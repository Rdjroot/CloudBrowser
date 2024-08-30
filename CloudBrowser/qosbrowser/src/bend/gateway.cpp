#include "gateway.h"
#include <QtConcurrent>
#include "src/config/common.h"

GateWay::GateWay(QObject *parent)
    : QObject{parent}
{}

GateWay::~GateWay()
{

}

void GateWay::send(int api, const QJsonValue &params)
{
    // QtConcurrent实际调用了线程池
    QtConcurrent::run([=]() {
        try {
            this->dispach(api, params);
        } catch (BaseException e) {
            mError(e.msg());
            emit MG->mSignal->error(api, e.msg(), params);
        } catch (...) {
            BaseException e =
                BaseException(EC_100000, STR("未知错误"));
            mError(e.msg());
            emit MG->mSignal->error(api, e.msg(), params);
        }
    });
}

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

void GateWay::apiLogin(const QJsonValue &value)
{
    QString secretId = value["secretId"].toString();
    QString secretKey = value["secretKey"].toString();
    MG->mCloud->login(secretId,secretKey);
}

void GateWay::apiGetBuckets(const QJsonValue &params)
{
    Q_UNUSED(params);
    MG->mCloud->getBuckets();
}

void GateWay::apiPutBucket(const QJsonValue &params)
{
    QString bucketName = params["bucketName"].toString();
    QString location = params["location"].toString();
    MG->mCloud->putBucket(bucketName,location);
}

void GateWay::apiDeleteBucket(const QJsonValue &params)
{
    QString bucketName = params["bucketName"].toString();
    MG->mCloud->deleteBucket(bucketName);
}

void GateWay::apiGetObjects(const QJsonValue &params)
{
    QString bucketName = params["bucketName"].toString();
    QString dir = params["dir"].toString();
    MG->mCloud->getObjects(bucketName, dir);
}


void GateWay::apiPutObject(const QJsonValue &params)
{
    QString jobId = params["jobId"].toString();  // 用于更新下载进度的任务id
    QString bucketName = params["bucketName"].toString();
    QString key = params["key"].toString();
    QString localPath = params["localPath"].toString();
    MG->mCloud->putObject(jobId, bucketName, key, localPath);
}


void GateWay::apiDownLoadObject(const QJsonValue &params)
{
    QString jobId = params["jobId"].toString();  // 用于更新上传进度的任务id
    QString bucketName = params["bucketName"].toString();
    QString key = params["key"].toString();
    QString localPath = params["localPath"].toString();
    MG->mCloud->getObject(jobId, bucketName, key, localPath);
}
