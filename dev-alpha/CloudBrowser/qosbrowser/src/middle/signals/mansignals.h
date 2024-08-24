#ifndef MANSIGNALS_H
#define MANSIGNALS_H

#include "src/middle/models/cloudmodels.h"
#include <QObject>

// #define MS ManSignals::instance()

/**
 * @brief 信号中心
 */
class ManSignals : public QObject
{
    Q_OBJECT
public:
    explicit ManSignals(QObject *parent = nullptr);
    static ManSignals* instance();

signals:
    void loginSuccess();
    void error(int api, const QString& msg, const QJsonValue &req);
    void unLogin();

    // 返回用户对应存储桶
    void bucketsSuccess(QList<MyBucket>);

    // 获取对象列表成功
    void objectsSuccess(const QList<MyObject>& objects);

    // 开始下载
    void startDownload(const QString &jobId, const QString &key, const QString &localPath, qulonglong total);
    // 下载对象进度
    void downloadProcess(const QString& jobid, qulonglong transferred, qulonglong total);
    // 下载对象成功
    void downloadSuccess(const QString& jobId);

    // 开始上传
    void startUpload(const QString &jobId, const QString &key, const QString &localPath);
    // 上传对象进度
    void uploadProcess(const QString& jobId, qulonglong transferred, qulonglong total);
    // 上传对象成功
    void uploadSuccess(const QString& jobId);
};

#endif // MANSIGNALS_H
