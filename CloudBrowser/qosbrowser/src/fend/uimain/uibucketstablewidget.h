#ifndef UIBUCKETSTABLEWIDGET_H
#define UIBUCKETSTABLEWIDGET_H

#include "src/middle/models/cloudmodels.h"
#include <QWidget>

namespace Ui {
class UiBucketsTableWidget;
}

/**
 * @brief 主界面存储桶表格窗体
 *
 *  用于展示当前存储桶、可创建、删除存储桶
 */
class UiBucketsTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UiBucketsTableWidget(QWidget *parent = nullptr);
    ~UiBucketsTableWidget();

private slots:
    /**
     * @brief 双击桶
     * @param index 索引
     */
    void on_tableView_doubleClicked(const QModelIndex &index);

    /**
     * @brief 获取桶列表(成功)-> 用于展示
     * @param buckets 桶列表
     */
    void onBucketsSuccess(const QList<MyBucket> &buckets);

    /**
     * @brief 翻页
     * @param start 开始
     * @param maxLen 最大行数
     */
    void onPageNumChanged(int start, int maxLen);

    /**
     * @brief 创建存储桶
     */
    void on_btnCreateBucket_clicked();
    /**
     * @brief 删除存储桶
     */
    void onDelBucket();
    /**
     * @brief 刷新页面
     */
    void on_btnRefresh_clicked();

private:
    Ui::UiBucketsTableWidget *ui;
};

#endif // UIBUCKETSTABLEWIDGET_H
