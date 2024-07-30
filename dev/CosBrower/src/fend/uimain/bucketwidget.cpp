#include "bucketwidget.h"
#include "ui_bucketwidget.h"

BucketWidget::BucketWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BucketWidget)
{
    ui->setupUi(this);
}

BucketWidget::~BucketWidget()
{
    delete ui;
}
