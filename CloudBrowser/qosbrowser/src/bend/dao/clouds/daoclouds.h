#ifndef DAOCLOUDS_H
#define DAOCLOUDS_H

#include "src/middle/models/cloudmodels.h"
#include <QList>
#include <QString>

// 传输进度回调函数
using TransProgressCallback = std::function<
    void(uint64_t transferred_size, uint64_t total_size, void*)>;

/**
 * @brief 操作云存储对象接口
 *
 */
class DaoClouds
{
public:
    // 构造函数
    DaoClouds(){};

    // 返回桶列表
    virtual QList<MyBucket> buckets() = 0;

    /**
     * @brief 登录云存储账号
     * @param secretId 账号
     * @param secretKey 密码
     * @return 桶列表
     */
    virtual QList<MyBucket> login(const QString secretId, const QString secretKey) = 0;

    /**
     * @brief 判断桶是否存在
     * @param bucketName 桶名
     * @return 结果
     */
    virtual bool isBucketExists(const QString& bucketName) =0;

    /**
     * @brief 获取桶地区
     * @param bucketName 桶名
     * @return 地区名
     */
    virtual QString getBucketLocation(const QString& bucketName) =0;

    /**
     * @brief 添加桶
     * @param bucketName 桶名
     * @param location 地区
     */
    virtual void putBucket(const QString& bucketName, const QString& location) =0;

    /**
     * @brief 删除桶
     * @param 桶名
     */
    virtual void deleteBucket(const QString& bucketName) =0;

    /**
     * @brief 获取桶内对象
     * @param bucketName 桶名
     * @param dir 桶内层级目录
     * @return 对象列表
     */
    virtual QList<MyObject> getObjects(const QString& bucketName,const QString &dir) =0;

    /**
     * @brief 上传对象
     * @param bucket  桶名
     * @param key  上传后在桶内的路径
     * @param localPath 本地路径
     * @param callback 回调函数
     */
    virtual void putObject(const QString &bucket,
                           const QString &key,
                           const QString &localPath,
                           const TransProgressCallback &callback) = 0;

    /**
     * @brief 下载对象
     * @param bucket  桶名
     * @param key 对象在桶内的路径
     * @param localPath 本地路径
     * @param callback 回调函数
     */
    virtual void getObject(const QString &bucket,
                           const QString &key,
                           const QString &localPath,
                           const TransProgressCallback &callback) = 0;

};
#endif // DAOCLOUDS_H
