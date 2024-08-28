#include "daocloudsmock.h"
#include "src/config/errorcode.h"
#include "src/config/exceptions.h"
#include "src/config/loggerproxy.h"
#include "src/middle/manglobal.h"
#include <QThread>

DaoCloudsMock::DaoCloudsMock(const QString &path) {
    // 将QVariant的内容转换为Json格式
    m_mock = FileHelper::readAllJson(path).toJsonValue();
}

// 把json文件里的数据数组化，每个元素也是一个jsonmap
QList<MyBucket> DaoCloudsMock::buckets() {
    QList<MyBucket> res;
    QJsonArray arr = m_mock["buckets"].toArray(); // 这里是把json里的数据数组化
    for (int i = 0; i < arr.count(); ++i) {
        QJsonValue v = arr[i];
        MyBucket bucket;
        bucket.name = v["name"].toString();
        bucket.location = v["location"].toString();
        bucket.createDate = v["create_date"].toString();

        res.append(bucket);
        mInfo(QString::fromUtf8("name[%1], location[%2], date[%3]")
                  .arg(bucket.name, bucket.location, bucket.createDate));
    }
    return res;
}

// mock调用登录接口
QList<MyBucket> DaoCloudsMock::login(const QString secretId,
                                     const QString secretKey) {
    QJsonArray arr = m_mock["users"].toArray();

    for (int i = 0; i < arr.size(); i++) {
        QJsonValue v = arr[i];
        // 这里应该是在模拟数据库里的登录信息
        if (secretId == v["secretId"].toString() &&
            secretKey == v["secretKey"].toString()) {
            return buckets(); // 因为是mock数据，这里没有对应的存储桶，所有用户用的同一个存储桶
        }
    }
    throw BaseException(
        EC_211000, QString::fromUtf8("请检查您的SecretId或SecretKey是否正确"));
}

bool DaoCloudsMock::isBucketExists(const QString &bucketName) {
    Q_UNUSED(bucketName);
    return false;
}

// TODO 这里没有真正进行模拟，需要的时候再进行
QString DaoCloudsMock::getBucketLocation(const QString &bucketName) {
    Q_UNUSED(bucketName);
    return QString();
}

void DaoCloudsMock::putBucket(const QString &bucketName,
                              const QString &location) {
    Q_UNUSED(bucketName);
    Q_UNUSED(location);
}

void DaoCloudsMock::deleteBucket(const QString &bucketName) {
    Q_UNUSED(bucketName);
}

QList<MyObject> DaoCloudsMock::getObjects(const QString &bucketName,
                                          const QString &dir) {
    Q_UNUSED(bucketName);
    Q_UNUSED(dir);
    return QList<MyObject>();
}

void DaoCloudsMock::putObject(const QString &bucket, const QString &key,
                              const QString &localPath,
                              const TransProgressCallback &callback) {
    Q_UNUSED(bucket);
    Q_UNUSED(key);
    Q_UNUSED(localPath);
    Q_UNUSED(callback);
}

void DaoCloudsMock::getObject(const QString &bucket, const QString &key,
                              const QString &localPath,
                              const TransProgressCallback &callback) {
    Q_UNUSED(bucket);
    Q_UNUSED(key);
    Q_UNUSED(localPath);
    Q_UNUSED(callback);
}
