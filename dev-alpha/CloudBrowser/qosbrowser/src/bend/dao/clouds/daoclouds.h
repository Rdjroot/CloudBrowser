#ifndef DAOCLOUDS_H
#define DAOCLOUDS_H

#include "src/middle/models/cloudmodels.h"
#include <QString>
#include<QList>
#include <QDir>

// 传输进度回调函数
using TransProgressCallback = std::function<
    void(uint64_t transferred_size, uint64_t total_size, void*)>;

class DaoClouds
{
public:
    DaoClouds(){};
    virtual QList<MyBucket> buckets() = 0;
    virtual QList<MyBucket> login(const QString secretId, const QString secretKey) = 0;

    virtual bool isBucketExists(const QString& bucketName) =0;
    virtual QString getBucketLocation(const QString& bucketName) =0;

    virtual void putBucket(const QString& bucketName, const QString& location) =0;
    virtual void deleteBucket(const QString& bucketName) =0;
    virtual QList<MyObject> getObjects(const QString& bucketName,const QString &dir) =0;

    virtual void putObject(const QString &bucket,
                           const QString &key,
                           const QString &localPath,
                           const TransProgressCallback &callback) = 0;

    virtual void getObject(const QString &bucket,
                           const QString &key,
                           const QString &localPath,
                           const TransProgressCallback &callback) = 0;


private:
};
#endif // DAOCLOUDS_H
