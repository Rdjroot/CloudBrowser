#ifndef UIBUCKETSLISTWIDGET_H
#define UIBUCKETSLISTWIDGET_H

#include <QWidget>
#include<src/bend/man/mancloud.h>

namespace Ui {
class UiBucketsListWidget;
}

// 左侧的搜索框和列表
class UiBucketsListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UiBucketsListWidget(QWidget *parent = nullptr);
    ~UiBucketsListWidget();

private slots:
    void onBucketSuccess(const QList<MyBucket> &buckets);

    void on_listView_doubleClicked(const QModelIndex &index);       // 双击效果
    void showBucketObjects(const QString& bucketName);
    void onTextEdited(const QString& text);

private:
    Ui::UiBucketsListWidget *ui;
};

#endif // UIBUCKETSLISTWIDGET_H
