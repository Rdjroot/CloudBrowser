#include "gateway.h"
#include <QtConcurrent>
#include "src/config/apis.h"
#include "src/bend/man/mancloud.h"
#include "src/config/errorcode.h"
#include "src/config/exceptions.h"
#include "src/config/loggerproxy.h"
#include "src/middle/signals/mansignals.h"
#include "src/middle/manglobal.h"

GateWay::GateWay(QObject *parent)
    : QObject{parent}
{}

GateWay::~GateWay()
{

}

/**
 * @brief 发送数据
 * @param api  调用的api接口ID
 * @param params  发送内容
 */
void GateWay::send(int api, const QJsonValue &params)
{
    // QtConcurrent实际调用了线程池
    QtConcurrent::run([=](){
        try{
            this->dispach(api,params);
        }
        catch(BaseException e)
        {
            mError(e.msg());
            emit MG->mSignal->error(api,e.msg(),params);
        }
        catch(...){
            BaseException e = BaseException(EC_100000, QString::fromLocal8Bit("未知错误"));
            mError(e.msg());
            emit MG->mSignal->error(api,e.msg(),params);
        }
    });
}

/**
 * @brief 根据api查询路由表，执行任务
 * @param api   路由表参数
 * @param value 携带数据
 */
void GateWay::dispach(int api, const QJsonValue &value)
{
    switch(api)
    {
        case API::LOGIN::NORMAL:
            apiLogin(value);
            break;

        case API::BUCKETS::LIST:
            apiGetBuckets(value);
            break;
        case API::BUCKETS::PUT:
            apiPutBucket(value);
            break;
        case API::BUCKETS::DEL:
            apiDeleteBucket(value);
            break;

        case API::OBJECTS::LIST:
            apiGetObjects(value);
            break;
        case API::OBJECTS::PUT:
            apiPutObject(value);
            break;
        case API::OBJECTS::GET:
            apiDownLoadObject(value);
            break;
        default:
            break;
    }
}
/**
 * @brief GateWay::apiLogin 执行登录
 * @param value
 */
void GateWay::apiLogin(const QJsonValue &value)
{
    QString secretId = value["secretId"].toString();
    QString secretKey = value["secretKey"].toString();
    MG->mCloud->login(secretId,secretKey);
}

/**
 * @brief GateWay::apiGetBuckets 获取桶列表
 * @param params
 */
void GateWay::apiGetBuckets(const QJsonValue &params)
{
    Q_UNUSED(params);
    MG->mCloud->getBuckets();
}

/**
 * @brief GateWay::apiPutBucket 创建桶
 * @param params
 */
void GateWay::apiPutBucket(const QJsonValue &params)
{
    QString bucketName = params["bucketName"].toString();
    QString location = params["location"].toString();
    MG->mCloud->putBucket(bucketName,location);
}

/**
 * @brief GateWay::apiDeleteBucket 删除存储桶
 * @param params
 */
void GateWay::apiDeleteBucket(const QJsonValue &params)
{
    QString bucketName = params["bucketName"].toString();
    MG->mCloud->deleteBucket(bucketName);
}

/**
 * @brief GateWay::apiGetObjects 获取对象列表
 * @param params
 */
void GateWay::apiGetObjects(const QJsonValue &params)
{
    QString bucketName = params["bucketName"].toString();
    QString dir = params["dir"].toString();
    MG->mCloud->getObjects(bucketName, dir);
}

/**
 * @brief GateWay::apiPutObject 上传对象
 * @param params
 */
void GateWay::apiPutObject(const QJsonValue &params)
{
    QString jobId = params["jobId"].toString();  // 用于更新下载进度的任务id
    QString bucketName = params["bucketName"].toString();
    QString key = params["key"].toString();
    QString localPath = params["localPath"].toString();
    qDebug()<< QString("2!!!! bucketName is %1.").arg(bucketName);
    qDebug()<< QString("3!!!! key is %1.").arg(key);
    qDebug()<< QString("4!!!! localPath is %1.").arg(localPath);
    MG->mCloud->putObject(jobId, bucketName, key, localPath);
}

/**
 * @brief GateWay::apiDownLoadObject 下载对象
 * @param params
 */
void GateWay::apiDownLoadObject(const QJsonValue &params)
{
    QString jobId = params["jobId"].toString();  // 用于更新上传进度的任务id
    QString bucketName = params["bucketName"].toString();
    QString key = params["key"].toString();
    QString localPath = params["localPath"].toString();
    MG->mCloud->getObject(jobId, bucketName, key, localPath);
}
