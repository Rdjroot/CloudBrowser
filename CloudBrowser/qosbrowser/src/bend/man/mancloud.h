#ifndef MANCLOUD_H
#define MANCLOUD_H

#include "src/middle/models/cloudmodels.h"
#include<QObject>
#include<QDebug>

/**
 * @brief 云对象存储类
 *
 * 业务层操作云对象接口，不感知底层对象存储
 *
 */
class ManCloud : public QObject
{
    Q_OBJECT
public:
    // 为了方便qt宏使用，不放在private中，但不要直接使用构造函数创建对象
    explicit ManCloud(QObject *parent = nullptr);
    ~ManCloud();

    /**
     * @brief  登录对象存储
     * @param secretId
     * @param secretKey
     */
    void login(QString secretId, QString secretKey);

    /**
     * @brief 获取存储桶列表返回前端
     *
     */
    void getBuckets();

    /**
     * @brief 增加存储桶
     * @param bucketName
     * @param location
     */
    void putBucket(const QString& bucketName, const QString& location);

    /**
     * @brief 删除存储桶
     * @param bucketName
     */
    void deleteBucket(const QString& bucketName);

    /**
     * @brief 获取对象列表返回前端
     * @param bucketName 桶名
     * @param dir 桶内目录
     */
    void getObjects(const QString& bucketName, const QString& dir="");

    /**
     * @brief 下载云对象
     * @param jobId
     * @param bucketName
     * @param key  桶内路径，eg: books/aaa.txt
     * @param localPath 本地路径
     */
    void getObject(const QString& jobId,
                   const QString& bucketName,
                   const QString& key,
                   const QString& localPath);

    /**
     * @brief 上传云对象
     * @param jobId
     * @param bucketName
     * @param key
     * @param localPath
     */
    void putObject(const QString& jobId,
                   const QString& bucketName,
                   const QString& key,
                   const QString& localPath);

    /**
     * @brief 返回当前桶名
     */
    QString currentBucketName() const;

    /**
     * @brief 返回当前桶内目录
     */
    QString currentDir() const;

private:
    /**
     * @brief 桶数据已经准备好，回传信号
     * @param buckets
     */
    void bucketsAlready(const QList<MyBucket> &buckets);

private:
    QString m_currentBucketName; // 记录当前对象所在存储桶的位置
    QString m_currentDir;        // 记录当前对象所在的父目录
};

#endif // MANBUCKETS_H
