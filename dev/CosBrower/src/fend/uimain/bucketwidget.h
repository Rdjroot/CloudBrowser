#ifndef BUCKETWIDGET_H
#define BUCKETWIDGET_H

#include <QWidget>
#include<src/bend/man/manbuckets.h>

namespace Ui {
class BucketWidget;
}

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
