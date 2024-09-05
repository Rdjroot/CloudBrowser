#ifndef UIUPLOAD_H
#define UIUPLOAD_H

#include <QJsonValue>
#include <QWidget>

namespace Ui {
class UiUpload;
}
class UiProgressWidget;

/**
 * @brief 上传列表展示
 */
class UiUpload : public QWidget
{
    Q_OBJECT

public:
    explicit UiUpload(QWidget *parent = nullptr);
    ~UiUpload();

private slots:
    /**
     * @brief 开始上传
     * @param jobId  任务id
     * @param key    下载对象
     * @param localPath 本地路径
     */
    void onStartUpload(const QString& jobId, const QString& key, const QString& localPath);

    /**
     * @brief 显示上传进度
     * @param jobId 任务id
     * @param transferedSize 已传输大小
     * @param totalSize 总大小
     */
    void onUploadProcess(const QString& jobId, qulonglong transferedSize, qulonglong totalSize);
    /**
     * @brief 上传成功
     * @param jobId 任务id
     */
    void onUploadSuccess(const QString& jobId);
    /**
     * @brief 上传出错
     * @param api 出错接口
     * @param msg 出错信息
     * @param req 请求头
     */
    void onError(int api, const QString& msg, const QJsonValue &req);

private:
    /**
     * @brief 找出对应的条目（进度条）
     * @param jobId 任务id
     * @return  进度条bar
     */
    UiProgressWidget *findTableWidgetItem(const QString& jobId);
    /**
     * @brief 初始化header
     */
    void initHeader();

private:
    Ui::UiUpload *ui;
};

#endif // UIUPLOAD_H
