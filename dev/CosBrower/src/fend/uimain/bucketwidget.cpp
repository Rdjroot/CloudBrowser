#include "bucketwidget.h"
#include "ui_bucketwidget.h"

BucketWidget::BucketWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BucketWidget)
{
    ui->setupUi(this);
    ui->listView->setModel(MB->model());
}

BucketWidget::~BucketWidget()
{
    delete ui;
}
