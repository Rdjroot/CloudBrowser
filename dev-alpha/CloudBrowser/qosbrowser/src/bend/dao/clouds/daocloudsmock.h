#ifndef DAOCLOUDSMOCK_H
#define DAOCLOUDSMOCK_H

#include "daoclouds.h"
#include <QJsonValue>
#include <QJsonArray>
#include <QDebug>
#include "src/helper/filehelper.h"

class DaoCloudsMock : public DaoClouds
{
public:
    DaoCloudsMock(const QString& path);
    QList<MyBucket> buckets() override;

    QList<MyBucket> login(const QString secretId, const QString secretKey);
    bool isBucketExists(const QString& bucketName) override;
    QString getBucketLocation(const QString& bucketName) override;

    void putBucket(const QString& bucketName, const QString& location) override;
    void deleteBucket(const QString& bucketName) override;
    QList<MyObject> getObjects(const QString& bucketName,const QString &dir) override;

    void putObject(const QString &bucket,
                           const QString &key,
                           const QString &localPath,
                           const TransProgressCallback &callback) override;

    void getObject(const QString &bucket,
                           const QString &key,
                           const QString &localPath,
                           const TransProgressCallback &callback) override;

private:
    QJsonValue m_mock;
};

#endif // DAOCLOUDSMOCK_H
