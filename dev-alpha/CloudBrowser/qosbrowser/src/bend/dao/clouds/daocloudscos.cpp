#include "daocloudscos.h"
#include"cos_api.h"
#include"src/config/exceptions.h"
#include"src/config/errorcode.h"
#include<QDebug>
#include <QDir>
#include <QFile>

using namespace qcloud_cos;

DaoCloudsCos::DaoCloudsCos()
{
    // qDebug() << "当前路径" << QDir::currentPath();
    // 这里需要放到执行文件所在目录的上一个目录
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

DaoCloudsCos::~DaoCloudsCos()
{
    delete m_config;
    m_config = nullptr;
}

// 获取存储桶列表
QList<MyBucket> DaoCloudsCos::buckets()
{
    QList<MyBucket> res;
    GetServiceReq req;
    GetServiceResp resp;
    CosAPI cos = CosAPI(*m_config);        // 这里会校验登录信息
    CosResult result = cos.GetService(req,&resp);

    // 获取云存储下的所有存储桶
    if(result.IsSucc())
    {
        std::vector<Bucket> bs = resp.GetBuckets();
        for (std::vector<Bucket>::const_iterator itr = bs.begin(); itr != bs.end(); ++itr) {
            const Bucket& bucket = *itr;
            MyBucket mybck;
            mybck.name = QString(bucket.m_name.c_str());
            mybck.location = QString(bucket.m_location.c_str());
            mybck.createDate = QString(bucket.m_create_date.c_str());
            res.append(mybck);
        }
    }
    else
    {
        QString msg = QString::fromUtf8("腾讯云错误码【%1】：%2")
                          .arg(result.GetErrorCode().c_str(),result.GetErrorMsg().c_str());
        throw BaseException(EC_211000,msg);
    }
    return res;
}

QList<MyBucket> DaoCloudsCos::login(const QString secretId, const QString secretKey)
{
    // std::cout << "secretId: "<< secretId.toStdString() <<std::endl;
    // std::cout << "secretKey: "<< secretKey.toStdString() <<std::endl;

    m_config->SetAccessKey(secretId.toStdString());
    m_config->SetSecretKey(secretKey.toStdString());

    m_config->SetRegion("ap-chengdu");
    return buckets();
}
