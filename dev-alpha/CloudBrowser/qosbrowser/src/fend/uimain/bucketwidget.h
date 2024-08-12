#ifndef BUCKETWIDGET_H
#define BUCKETWIDGET_H

#include <QWidget>
#include<src/bend/man/mancloud.h>

namespace Ui {
class BucketWidget;
}

// 左侧的搜索框和列表
class BucketWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BucketWidget(QWidget *parent = nullptr);
    ~BucketWidget();

private:
    Ui::BucketWidget *ui;
};

#endif // BUCKETWIDGET_H
