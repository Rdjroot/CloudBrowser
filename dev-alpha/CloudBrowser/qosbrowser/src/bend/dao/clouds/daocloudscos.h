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
    DaoCloudsCos();
    ~DaoCloudsCos();
    QList<MyBucket> buckets()  override;                // 存储桶列表
    QList<MyBucket> login(const QString secretId, const QString secretKey) override;    // 登录

    bool isBucketExists(const QString& bucketName) override ;               // 判断存储桶是否存在
    QString getBucketLocation(const QString& bucketName) override;          // 获取存储桶的location

    void putBucket(const QString& bucketName, const QString& location) override;    // 增加存储桶
    void deleteBucket(const QString& bucketName) override;      // 删除存储桶

    QList<MyObject> getObjects(const QString& bucketName,const QString &dir) override; // 获取存储桶目录下的对象（文件）

    bool isObjectExists(const QString &bucketname, const QString &key);

    void putObject(const QString &bucketName,
                           const QString &key,
                           const QString &localPath,
                           const TransProgressCallback &callback) override;

    void getObject(const QString &bucketName,
                           const QString &key,
                           const QString &localPath,
                           const TransProgressCallback &callback) override;

private:
    QList<MyObject> getDirList(qcloud_cos::GetBucketResp &resp, const QString &dir);
    QList<MyObject> getFileList(qcloud_cos::GetBucketResp &resp, const QString &dir);
    MyBucket getBucketByName(const QString &bucketName);
    void throwError(const QString& code, qcloud_cos::CosResult& result);        // 异常处理

private:
    qcloud_cos::CosConfig *m_config = nullptr;
};

#endif // DAOCLOUDSCOS_H
