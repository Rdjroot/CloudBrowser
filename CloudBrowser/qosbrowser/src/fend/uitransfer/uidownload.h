#ifndef UIDOWNLOAD_H
#define UIDOWNLOAD_H

#include <QWidget>
#include <QJsonObject>

namespace Ui {
class UiDownload;
}

class UiProgressWidget;

/**
 * @brief 下载列表展示
 */

class UiDownload : public QWidget
{
    Q_OBJECT

public:
    explicit UiDownload(QWidget *parent = nullptr);
    ~UiDownload();

private slots:

    /**
     * @brief 开始下载
     * @param jobId     任务id
     * @param key       下载对象
     * @param localPath    本地路径
     * @param total     文件大小
     */
    void onStartDownload(const QString& jobId, const QString& key, const QString& localPath, qulonglong total);

    /**
     * @brief 显示下载进度
     * @param jobId 任务id
     * @param transferedSize 已传输大小
     * @param totalSize 总大小
     */
    void onDownloadProcess(const QString& jobId, qulonglong transferedSize, qulonglong totalSize);

    /**
     * @brief 下载成功
     * @param jobId 任务id
     */
    void onDownloadSuccess(const QString& jobId);
    /**
     * @brief 下载出错
     * @param api 出错接口
     * @param msg 出错信息
     * @param req 请求头
     */
    void onError(int api, const QString &msg, const QJsonValue &req);
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
    Ui::UiDownload *ui;
};

#endif // UIDOWNLOAD_H
