#ifndef MANCLOUD_H
#define MANCLOUD_H

#include "src/middle/models/cloudmodels.h"
#include<QObject>
#include<QDebug>


/**
 * @brief 云对象存储类，用于对对象存储进行操作
 */
class ManCloud : public QObject
{
    Q_OBJECT
public:
    // 为了方便qt宏使用，不放在private中，但不要直接使用构造函数创建对象
    explicit ManCloud(QObject *parent = nullptr);
    ~ManCloud();

    void login(QString secretId, QString secretKey);

    // 桶接口操作
    void getBuckets();
    void putBucket(const QString& bucketName, const QString& location);
    void deleteBucket(const QString& bucketName);

    // 对象操作接口
    void getObjects(const QString& bucketName, const QString& dir="");
    void getObject(const QString& jobId,
                   const QString& bucketName,
                   const QString& key,
                   const QString& localPath);
    void putObject(const QString& jobId,
                   const QString& bucketName,
                   const QString& key,
                   const QString& localPath);

    QString currentBucketName() const;
    QString currentDir() const;
private:
    void bucketsAlready(const QList<MyBucket> &buckets);

private:
    QString m_currentBucketName;        // 记录当前对象所在存储桶的位置
    QString m_currentDir;           // 记录当前对象所在的父目录
};

#endif // MANBUCKETS_H
