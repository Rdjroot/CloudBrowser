#include "daocloudscos.h"
#include"cos_api.h"
#include"src/config/common.h"
#include<QDebug>
#include<string>
using namespace qcloud_cos;

DaoCloudsCos::DaoCloudsCos()
{
    // 这里需要放到执行文件(.exe)所在目录的上一个目录
    m_config = new CosConfig("./cosconfig.json");
    mWarning("The program uses Tencent cloud object storage.");
}

/**
 * @brief 释放指针
 */
DaoCloudsCos::~DaoCloudsCos()
{
    delete m_config;
    m_config = nullptr;
}

QList<MyBucket> DaoCloudsCos::buckets()
{
    GetServiceReq req;
    GetServiceResp resp;
    CosAPI cos = CosAPI(*m_config);

    // 请求登录云存储账户，返回结果
    CosResult result = cos.GetService(req, &resp);

    if (!result.IsSucc()) {
        // 用户登录用户密码有误
        throwError(EC_211000, result);
    }

    QList<MyBucket> res;
    // 这里的Bucket是cos API中的类
    std::vector<Bucket> bs = resp.GetBuckets();
    for (std::vector<Bucket>::const_iterator itr = bs.begin(); itr != bs.end(); ++itr)
    {
        const Bucket& v = *itr;

        MyBucket b;
        b.name = QString(v.m_name.c_str());
        b.location = QString(v.m_location.c_str());
        b.createDate = QString(v.m_create_date.c_str());
        res.append(b);
    }
    return res;
}

QList<MyBucket> DaoCloudsCos::login(const QString secretId, const QString secretKey)
{
    m_config->SetAccessKey(secretId.toStdString());
    m_config->SetSecretKey(secretKey.toStdString());

    // 设置默认的地区为成都
    m_config->SetRegion("ap-chengdu");
    return buckets();
}

bool DaoCloudsCos::isBucketExists(const QString &bucketName)
{
    MyBucket bucket = getBucketByName(bucketName);
    return bucket.isValid();
}

QString DaoCloudsCos::getBucketLocation(const QString &bucketName)
{
    CosAPI cos = CosAPI(*m_config);
    QString location(cos.GetBucketLocation(bucketName.toStdString()).c_str());
    if (location != "") {
        return location;
    }

    MyBucket bucket = getBucketByName(bucketName);
    if (bucket.isValid()) {
        return bucket.location;
    }
    throw BaseException(EC_332000, STR("获取桶位置失败 %1").arg(bucketName));
}

void DaoCloudsCos::putBucket(const QString &bucketName, const QString &location)
{
    if(isBucketExists(bucketName))
    {
        return;
    }

    PutBucketReq req(bucketName.toLocal8Bit().data());
    PutBucketResp resp;

    m_config->SetRegion(location.toStdString());    // 重新设置地区
    CosAPI cos(*m_config);
    CosResult result = cos.PutBucket(req, &resp);
    if(!result.IsSucc())
    {
        throwError(EC_331100, result);
    }
}


void DaoCloudsCos::deleteBucket(const QString &bucketName)
{
    // 删除存储桶，只能删除空的存储桶
    if (!isBucketExists(bucketName)) {
        return;
    }

    DeleteBucketReq req(bucketName.toLocal8Bit().data());
    DeleteBucketResp resp;
    QString location = getBucketLocation(bucketName);
    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);

    // 响应对象提供了获取和处理服务器返回结果的机制，
    // 确保了 API 调用能够正确地处理和反馈操作的结果
    CosResult result = cos.DeleteBucket(req, &resp);
    if (!result.IsSucc()) {
        throwError(EC_331300, result);
    }
}

QList<MyObject> DaoCloudsCos::getObjects(const QString &bucketName, const QString &dir)
{
    GetBucketReq req(bucketName.toLocal8Bit().data());
    if (dir != "")
        req.SetPrefix(dir.toLocal8Bit().data());
    req.SetDelimiter("/");

    GetBucketResp resp;
    QString location = getBucketLocation(bucketName); // 设置地址
    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);

    CosResult result = cos.GetBucket(req, &resp); // 获取结果
    if (!result.IsSucc()) {
        throwError(EC_331200, result);
    }
    // 获取该桶层级下的所有文件夹和文件对象
    return getDirList(resp, dir) + getFileList(resp, dir);
}

bool DaoCloudsCos::isObjectExists(const QString &bucketname, const QString &key)
{
    QString location = getBucketLocation(bucketname);
    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);
    // 判断文件对象是否存在
    return cos.IsObjectExist(bucketname.toStdString(), key.toLocal8Bit().data());
}

void DaoCloudsCos::throwError(const QString &code, CosResult &result)
{
    QString msg = QString::fromUtf8("腾讯云错误码【%1】：%2")
                      .arg(result.GetErrorCode().c_str(), result.GetErrorMsg().c_str());
    qDebug() << msg;                    // 这里会被捕获在控制台输出
    throw BaseException(code, msg);     // 输出到日志里
}

MyBucket DaoCloudsCos::getBucketByName(const QString &bucketName)
{
    QList<MyBucket> bs = buckets();
    for (const auto& b: qAsConst(bs)) {
        if (b.name == bucketName) {
            return b;
        }
    }
    return MyBucket();
}

void DaoCloudsCos::putObject(const QString &bucketName, const QString &key,
                             const QString &localPath,
                             const TransProgressCallback &callback) {
    // 初始化上传
    SharedAsyncContext context;
    std::string bucket_name = bucketName.toLocal8Bit().data();
    std::string local_file = localPath.toLocal8Bit().data();
    std::string object_name =key.toLocal8Bit().data();
    std::setlocale(LC_ALL, ".UTF-8");      // 这一步会处理路径中的中文符号，必不可少

    // 异步上传
    AsyncPutObjectReq put_req(bucket_name,
                             object_name,
                              local_file);

    // 设置上传进度回调
    if (callback) {
        put_req.SetTransferProgressCallback(callback);
    }

    QString location = getBucketLocation(bucketName);
    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);

    context = cos.AsyncPutObject(put_req);
    context->WaitUntilFinish(); // 等待上传结束

    CosResult result = context->GetResult();
    if (!result.IsSucc()) {
        throwError(EC_332400, result);
    }
}

void DaoCloudsCos::getObject(const QString &bucketName, const QString &key,
                             const QString &localPath,
                             const TransProgressCallback &callback) {
    // 下载初始化
    SharedAsyncContext context;
    // 异步下载
    AsyncGetObjectReq get_req(bucketName.toLocal8Bit().data(),
                              key.toLocal8Bit().data(),
                              localPath.toLocal8Bit().data());

    if (callback) {
        get_req.SetTransferProgressCallback(callback);
    }

    QString location = getBucketLocation(bucketName);
    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);

    // 开始下载
    context = cos.AsyncGetObject(get_req);
    context->WaitUntilFinish();
    CosResult result = context->GetResult();
    if (!result.IsSucc()) {
        throwError(EC_332500, result);
    }
}

QList<MyObject> DaoCloudsCos::getDirList(qcloud_cos::GetBucketResp &resp, const QString &dir)
{
    QList<MyObject> res;
    std::vector<std::string> cs = resp.GetCommonPrefixes(); // 获取目录列表
    for(int i = 0; i < cs.size(); i++)
    {
        QString key(cs[i].c_str());     // 这里是在桶中完整的路径，如：books/aaa.txt

        MyObject object;
        object.dir = dir;
        object.name = key.mid(dir.size());  // 将末位目录进行截取，dir.size是截取起始位置
        object.lastmodified = "-";
        object.key = key;
        res.append(object);
    }
    return res;
}

QList<MyObject> DaoCloudsCos::getFileList(GetBucketResp &resp, const QString &dir)
{
    QList<MyObject> res;
    // 获取文件列表
    const std::vector<Content>& contents = resp.GetContents();
    for(std::vector<Content>::const_iterator itr = contents.begin(); itr!=contents.end(); ++itr)
    {
        const Content& content = *itr;
        QString key(content.m_key.c_str());

        QString name = key.mid(dir.size());     // 目录尾节选出文件名
        if(key != dir)                          // 只有非目录，会加入res
        {
            MyObject object;
            object.name = name;
            object.lastmodified = QString(content.m_last_modified.c_str());
            object.size = QString(content.m_size.c_str()).toULongLong();
            object.dir = dir;
            object.key = key;
            res.append(object);
        }
    }
    return res;
}
