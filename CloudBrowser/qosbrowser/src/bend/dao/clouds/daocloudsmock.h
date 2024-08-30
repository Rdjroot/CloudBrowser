#ifndef DAOCLOUDSMOCK_H
#define DAOCLOUDSMOCK_H

#include "daoclouds.h"
#include <QJsonValue>
#include <QJsonArray>
#include <QDebug>

/**
 * @brief 构造数据模拟云存储操作
 */
class DaoCloudsMock : public DaoClouds
{
public:
    DaoCloudsMock(const QString& path);
    // 返回桶列表
    QList<MyBucket> buckets() override;

    /**
     * @brief 登录云存储账号
     * @param secretId 账号
     * @param secretKey 密码
     * @return 桶列表
     */
    QList<MyBucket> login(const QString secretId, const QString secretKey);

    /**
     * @brief 判断桶是否存在
     * @param bucketName 桶名
     * @return 结果
     */
    bool isBucketExists(const QString& bucketName) override;

    /**
     * @brief 获取桶地区
     * @param bucketName 桶名
     * @return 地区名
     */
    QString getBucketLocation(const QString& bucketName) override;

    /**
     * @brief 添加桶
     * @param bucketName 桶名
     * @param location 地区
     */
    void putBucket(const QString& bucketName, const QString& location) override;

    /**
     * @brief 删除桶
     * @param 桶名
     */
    void deleteBucket(const QString& bucketName) override;

    /**
     * @brief 获取桶内对象
     * @param bucketName 桶名
     * @param dir 桶内层级目录
     * @return 对象列表
     */
    QList<MyObject> getObjects(const QString& bucketName,const QString &dir) override;

    /**
     * @brief 上传对象
     * @param bucket  桶名
     * @param key  上传后在桶内的路径
     * @param localPath 本地路径
     * @param callback 回调函数
     */
    void putObject(const QString &bucket,
                           const QString &key,
                           const QString &localPath,
                           const TransProgressCallback &callback) override;

    /**
     * @brief 下载对象
     * @param bucket  桶名
     * @param key 对象在桶内的路径
     * @param localPath 本地路径
     * @param callback 回调函数
     */
    void getObject(const QString &bucket,
                           const QString &key,
                           const QString &localPath,
                           const TransProgressCallback &callback) override;

private:
    QJsonValue m_mock;
};

#endif // DAOCLOUDSMOCK_H
