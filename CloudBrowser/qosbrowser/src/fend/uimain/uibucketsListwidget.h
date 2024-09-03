#ifndef UIBUCKETSLISTWIDGET_H
#define UIBUCKETSLISTWIDGET_H

#include <QWidget>
#include<src/bend/man/mancloud.h>

namespace Ui {
class UiBucketsListWidget;
}

/**
 * @brief 左侧搜索框和桶列表窗口
 *
 */
class UiBucketsListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UiBucketsListWidget(QWidget *parent = nullptr);
    ~UiBucketsListWidget();

private slots:
    /**
     * @brief 初始化窗体（含联想词条、桶列表）
     * @param buckets 后台获取的桶列表
     */
    void onBucketSuccess(const QList<MyBucket> &buckets);

    /**
     * @brief 双击表格跳转存储桶
     * @param index 索引
     */
    void on_listView_doubleClicked(const QModelIndex &index);       // 双击效果

    /**
     * @brief 在tableview中展示对应桶内容
     * @param bucketName 桶名
     */
    void showBucketObjects(const QString& bucketName);

    /**
     * @brief 搜索框搜索
     * @param text 输入内容
     */
    void onTextEdited(const QString& text);

private:
    Ui::UiBucketsListWidget *ui;
};

#endif // UIBUCKETSLISTWIDGET_H
