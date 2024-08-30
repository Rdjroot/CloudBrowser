#ifndef DAOCLOUDSCOS_H
#define DAOCLOUDSCOS_H

#include "daoclouds.h"
#include <cos_config.h>
#include <op/cos_result.h>
#include <response/bucket_resp.h>

/**
 * @brief 对接腾讯云接口，进行存储桶的增删改查
 *
 */
class DaoCloudsCos : public DaoClouds
{
public:
    /**
     * @brief 构造函数：使用配置文件初始化
     */
    DaoCloudsCos();
    ~DaoCloudsCos();

    // 返回桶列表
    QList<MyBucket> buckets()  override;

    /**
     * @brief 登录云存储账号
     * @param secretId 账号
     * @param secretKey 密码
     * @return 桶列表
     */
    QList<MyBucket> login(const QString secretId, const QString secretKey) override;    // 登录

    /**
     * @brief 判断桶是否存在
     * @param bucketName 桶名
     * @return 结果
     */
    bool isBucketExists(const QString& bucketName) override ;               // 判断存储桶是否存在

    /**
     * @brief 获取桶地区
     * @param bucketName 桶名
     * @return 地区名
     */
    QString getBucketLocation(const QString& bucketName) override;          // 获取存储桶的location

    /**
     * @brief 添加桶
     * @param bucketName 桶名
     * @param location 地区
     */
    void putBucket(const QString& bucketName, const QString& location) override;    // 增加存储桶

    /**
     * @brief 删除桶
     * @param 桶名
     */
    void deleteBucket(const QString& bucketName) override;      // 删除存储桶

    /**
     * @brief 获取桶内对象
     * @param bucketName 桶名
     * @param dir 桶内层级目录
     * @return 对象列表
     */
    QList<MyObject> getObjects(const QString& bucketName,const QString &dir) override; // 获取存储桶目录下的对象（文件）

    /**
     * @brief 对象是否存在
     * @param bucketname 桶名
     * @param key 桶内路径
     * @return bool结果
     */
    bool isObjectExists(const QString &bucketname, const QString &key);

    /**
     * @brief 上传对象
     * @param bucket  桶名
     * @param key  上传后在桶内的路径
     * @param localPath 本地路径
     * @param callback 回调函数
     */
    void putObject(const QString &bucketName,
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
    void getObject(const QString &bucketName,
                           const QString &key,
                           const QString &localPath,
                           const TransProgressCallback &callback) override;

private:
    /**
     * @brief 获取当前层级文件夹
     * @param resp 响应头
     * @param dir 目录
     * @return 文件夹列表
     */
    QList<MyObject> getDirList(qcloud_cos::GetBucketResp &resp, const QString &dir);

    /**
     * @brief 获取当前层级下文件对象
     * @param resp 响应头
     * @param dir 层级目录
     * @return 文件对象列表
     */
    QList<MyObject> getFileList(qcloud_cos::GetBucketResp &resp, const QString &dir);

    /**
     * @brief 根据桶名获取桶
     * @param bucketName  桶名
     * @return 桶对象
     */
    MyBucket getBucketByName(const QString &bucketName);

    /**
     * @brief 异常处理
     * @param code 错误码
     * @param result 响应结果
     */
    void throwError(const QString& code, qcloud_cos::CosResult& result);

private:
    qcloud_cos::CosConfig *m_config = nullptr;
};

#endif // DAOCLOUDSCOS_H
