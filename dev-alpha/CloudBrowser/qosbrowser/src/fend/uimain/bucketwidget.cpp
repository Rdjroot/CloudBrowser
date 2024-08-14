#include "bucketwidget.h"
#include "src/middle/manglobal.h"
#include "src/middle/manmodels.h"
#include "ui_bucketwidget.h"

BucketWidget::BucketWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BucketWidget)
{
    ui->setupUi(this);
    ui->listView->setModel(MG->mModels->model());   // 设置视图
}

BucketWidget::~BucketWidget()
{
    delete ui;
}
