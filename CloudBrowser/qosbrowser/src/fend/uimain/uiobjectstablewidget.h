#ifndef UIOBJECTSTABLEWIDGET_H
#define UIOBJECTSTABLEWIDGET_H

#include "src/middle/models/cloudmodels.h"
#include <QWidget>

namespace Ui {
class UiObjectsTableWidget;
}

/**
 * @brief 云存储对象窗体
 *
 * 支持查看，下载、上传对象文件
 *
 */
class UiObjectsTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UiObjectsTableWidget(QWidget *parent = nullptr);
    ~UiObjectsTableWidget();

private slots:
    /**
     * @brief 返回桶列表
     */
    void on_btnBuckets_clicked();

    /**
     * @brief 双击进入目录
     * @param index 索引
     */
    void on_tableView_doubleClicked(const QModelIndex &index);

    /**
     * @brief 成功获取对象
     * @param objects 对象列表
     */
    void onObjectsSuccess(const QList<MyObject>& objects);

    /**
     * @brief 翻页
     * @param start 起始条目
     * @param maxLen 一页最大行数
     */
    void onPageNumChanged(int start, int maxLen);

    /**
     * @brief 目录更替
     * @param newPath 新目录
     */
    void onPathChanged(const QString& newPath);

    /**
     * @brief 刷新页面
     */
    void on_btnRefresh_clicked();

    /**
     * @brief 上传
     */
    void on_btnUpload_clicked();

    /**
     * @brief 上传成功
     * @param jobId  任务id
     */
    void onUploadSuccess(const QString& jobId);

    /**
     * @brief 下载
     */
    void on_btnDownload_clicked();

    /**
     * @brief 下载成功
     * @param jobId
     */
    void onDownloadSuccess(const QString& jobId);

private:
    Ui::UiObjectsTableWidget *ui;
};

#endif // UIOBJECTSTABLEWIDGET_H
