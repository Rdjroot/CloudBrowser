#include "mancloud.h"
#include "src/middle/manglobal.h"
#include "src/middle/signals/mansignals.h"
#include "src/plugins/manplugin.h"


ManCloud::ManCloud(QObject *parent) : QObject(parent)
{

}

ManCloud::~ManCloud()
{

}

/**
 * @brief  登录云对象存储
 * @param secretId
 * @param secretKey
 */
void ManCloud::login(QString secretId, QString secretKey)
{
    QList<MyBucket> buckets = MG->mPlugin->clouds()->login(secretId,secretKey);

    // 在这里发送登录信号
    emit MG->mSignal->loginSuccess();
    bucketsAlready(buckets);
}

/**
 * @brief ManCloud::getBuckets 获取存储桶列表
 */
void ManCloud::getBuckets()
{
    QList<MyBucket> buckets = MG->mPlugin->clouds()->buckets();
    bucketsAlready(buckets);
}

/**
 * @brief ManCloud::putBucket 创建存储桶
 * @param bucketName
 * @param location
 */
void ManCloud::putBucket(const QString &bucketName, const QString &location)
{
    MG->mPlugin->clouds()->putBucket(bucketName, location);
    getBuckets();           // 更新本地存储桶
}

/**
 * @brief ManCloud::deleteBucket 删除存储桶
 * @param bucketName
 */
void ManCloud::deleteBucket(const QString &bucketName)
{
    MG->mPlugin->clouds()->deleteBucket(bucketName);
    getBuckets();
}

/**
 * @brief ManCloud::getObjects 获取对象列表
 * @param bucketName
 * @param dir
 */
void ManCloud::getObjects(const QString &bucketName, const QString &dir)
{
    QList<MyObject> objs = MG->mPlugin->clouds()->getObjects(bucketName, dir);
    m_currentBucketName = bucketName;
    m_currentDir = dir;
    emit MG->mSignal->objectsSuccess(objs);
}

/**
 * @brief ManCloud::getObject 下载云对象
 * @param jobId
 * @param bucketName
 * @param key
 * @param localPath
 */
void ManCloud::getObject(const QString &jobId, const QString &bucketName, const QString &key, const QString &localPath)
{
    // transferred_size 已经传送的大小，total_size 需要传输的总大小
    auto callback = [=](qulonglong transferred_size, qulonglong total_size, void *) {
        assert(transferred_size <= total_size);
        if (0 == transferred_size % (1024*512)) {
            emit MG->mSignal->downloadProcess(jobId, transferred_size, total_size);
        }
    };
    MG->mPlugin->clouds()->getObject(bucketName, key, localPath, callback);
    emit MG->mSignal->downloadSuccess(jobId);
}

/**
 * @brief ManCloud::putObject 上传云对象
 * @param jobId
 * @param bucketName
 * @param key
 * @param localPath
 */
void ManCloud::putObject(const QString &jobId, const QString &bucketName, const QString &key, const QString &localPath)
{
    auto callback = [=](qulonglong transferred_size, qulonglong total_size, void *) {
        assert(transferred_size <= total_size);
        if (0 == transferred_size % (1024*512)) {
            emit MG->mSignal->uploadProcess(jobId, transferred_size, total_size);
        }
    };
    MG->mPlugin->clouds()->putObject(bucketName, key, localPath, callback);
    emit MG->mSignal->uploadSuccess(jobId);
}

QString ManCloud::currentBucketName() const
{
    return m_currentBucketName;
}

QString ManCloud::currentDir() const
{
    return m_currentDir;
}

/**
 * @brief 桶数据已经准备好
 * @param buckets
 */
void ManCloud::bucketsAlready(const QList<MyBucket> &buckets)
{
    m_currentBucketName.clear();
    m_currentDir.clear();
    emit MG->mSignal->bucketsSuccess(buckets);
}
