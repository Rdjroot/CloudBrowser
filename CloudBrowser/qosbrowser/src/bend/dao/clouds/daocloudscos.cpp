#include "daocloudscos.h"
#include"cos_api.h"
#include"src/config/exceptions.h"
#include"src/config/errorcode.h"
#include<QDebug>
#include <QDir>
#include <QFile>

using namespace qcloud_cos;

/**
 * @brief DaoCloudsCos::DaoCloudsCos 使用配置文件初始化
 */
DaoCloudsCos::DaoCloudsCos()
{
    // 这里需要放到执行文件(.exe)所在目录的上一个目录
    QString relativePath = "./cosconfig.json";
    QFile file(relativePath);
    if(file.exists())
    {
        m_config = new CosConfig(relativePath.toStdString());
        qDebug() <<"使用的相对路径.";
    }
    else
    {
        QString obsolutePath = "F:\\Code\\CloudStorage\\dev-alpha\\CloudBrowser\\qosbrowser\\static\\configs\\cosconfig.json";
        m_config = new CosConfig(obsolutePath.toStdString());
        qDebug() <<"使用的绝对路径.";
    }
}

/**
 * @brief DaoCloudsCos::~DaoCloudsCos 释放指针
 */
DaoCloudsCos::~DaoCloudsCos()
{
    delete m_config;
    m_config = nullptr;
}

/**
 * @brief DaoCloudsCos::buckets 获取存储桶列表
 * @return
 */
QList<MyBucket> DaoCloudsCos::buckets()
{
    QList<MyBucket> res;

    GetServiceReq req;
    GetServiceResp resp;
    CosAPI cos = CosAPI(*m_config);
    CosResult result = cos.GetService(req, &resp);

    if (!result.IsSucc()) {
        throwError(EC_211000, result);
    }

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

/**
 * @brief DaoCloudsCos::login 腾讯云对象存储登录
 * @param secretId
 * @param secretKey
 * @return
 */
QList<MyBucket> DaoCloudsCos::login(const QString secretId, const QString secretKey)
{
    m_config->SetAccessKey(secretId.toStdString());
    m_config->SetSecretKey(secretKey.toStdString());

    m_config->SetRegion("ap-chengdu");
    return buckets();
}

/**
 * @brief DaoCloudsCos::isBucketExists  查看存储桶是否存在
 * @param bucketName   桶名称
 * @return bool
 */
bool DaoCloudsCos::isBucketExists(const QString &bucketName)
{
    MyBucket bucket = getBucketByName(bucketName);
    return bucket.isValid();
}

/**
 * @brief DaoCloudsCos::getBucketLocation 获取存储桶的地区
 * @param bucketName  桶名称
 * @return 地区
 */
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
    throw BaseException(EC_332000, QString::fromLocal8Bit("获取桶位置失败 %1").arg(bucketName));

}


/**
 * @brief DaoCloudsCos::putBucket 创建存储桶
 * @param bucketName    桶名称
 * @param location  地区
 */
void DaoCloudsCos::putBucket(const QString &bucketName, const QString &location)
{
    if(isBucketExists(bucketName))
    {
        return;
    }

    PutBucketReq req(bucketName.toLocal8Bit().data());
    PutBucketResp resp;

    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);
    CosResult result = cos.PutBucket(req, &resp);
    if(!result.IsSucc())
    {
        throwError(EC_331100, result);
    }
}

// 删除存储桶，只能删除空的存储桶
void DaoCloudsCos::deleteBucket(const QString &bucketName)
{
    if (!isBucketExists(bucketName)) {
        return;
    }

    DeleteBucketReq req(bucketName.toLocal8Bit().data());
    DeleteBucketResp resp;
    QString location = getBucketLocation(bucketName);
    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);
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
    QString location = getBucketLocation(bucketName);       // 设置地址
    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);

    CosResult result = cos.GetBucket(req, &resp); // 获取结果
    if(!result.IsSucc())
    {
        throwError(EC_331200, result);
    }
    return getDirList(resp, dir) + getFileList(resp,dir);
}

bool DaoCloudsCos::isObjectExists(const QString &bucketname, const QString &key)
{
    QString location = getBucketLocation(bucketname);
    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);
    return cos.IsObjectExist(bucketname.toStdString(), key.toLocal8Bit().data());
}

void DaoCloudsCos::throwError(const QString &code, CosResult &result)
{
    QString msg = QString::fromUtf8("腾讯云错误码【%1】：%2")
                      .arg(result.GetErrorCode().c_str(), result.GetErrorMsg().c_str());
    qDebug() << msg;    // 这里会被捕获
    throw BaseException(code,msg);
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


/**
 * @brief DaoCloudsCos::putObject 上传文件到存储桶
 * @param bucketName    桶名称
 * @param key       上传后的名称
 * @param localPath 本地文件路径
 * @param callback  回调函数，可为nullptr
 */
void DaoCloudsCos::putObject(const QString &bucketName, const QString &key,
                             const QString &localPath,
                             const TransProgressCallback &callback) {
    // 初始化上传
    SharedAsyncContext context;
    std::string bucket_name = bucketName.toLocal8Bit().data();
    std::string local_file = localPath.toLocal8Bit().data();
    std::string object_name =key.toLocal8Bit().data();
    std::setlocale(LC_ALL, ".UTF-8");               // 关键的一步！
    std::cout << "5!!!! AsyncPutObjectReq args are bucketName: "
              << bucket_name
              << ", key: " << object_name
              << ", localPath: " << local_file<< std::endl;

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

/**
 * @brief DaoCloudsCos::getObject 从云盘下载文件到本地
 * @param bucketName    桶名称
 * @param key       下载文件名
 * @param localPath 下载本地路径
 * @param callback  回调函数，可为nullptr
 */
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

/**
 * @brief DaoCloudsCos::getDirList 获取目录列表
 * @param resp
 * @param dir
 * @return
 */
QList<MyObject> DaoCloudsCos::getDirList(qcloud_cos::GetBucketResp &resp, const QString &dir)
{
    QList<MyObject> res;
    std::vector<std::string> cs = resp.GetCommonPrefixes(); // 获取目录列表
    for(int i = 0; i < cs.size(); i++)
    {
        QString key(cs[i].c_str());
        // qDebug() <<"dir: "<< key;

        MyObject object;
        object.dir = dir;
        object.name = key.mid(dir.size());  // 将目录进行截取
        object.lastmodified = "-";
        object.key = key;
        res.append(object);
        // qDebug() <<"dirName"<<object.name;
    }
    return res;
}

/**
 * @brief DaoCloudsCos::getFileList 获取文件列表
 * @param resp
 * @param dir
 * @return
 */
QList<MyObject> DaoCloudsCos::getFileList(GetBucketResp &resp, const QString &dir)
{
    QList<MyObject> res;
    // 获取文件列表
    const std::vector<Content>& contents = resp.GetContents();
    for(std::vector<Content>::const_iterator itr = contents.begin(); itr!=contents.end(); ++itr)
    {
        const Content& content = *itr;
        QString key(content.m_key.c_str());
        // qDebug() << "file: "<<key;          // 打印内容看看

        QString name = key.mid(dir.size());     // 从某个位置开始节选字符串
        if(key != dir)
        {
            MyObject object;
            object.name = name;
            object.lastmodified = QString(content.m_last_modified.c_str());
            object.size = QString(content.m_size.c_str()).toULongLong();
            object.dir = dir;
            object.key = key;
            res.append(object);
            // qDebug() << "fileName" << name;
        }
    }
    return res;
}
