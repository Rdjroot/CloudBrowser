#include "objectswidget.h"
#include "src/middle/manmodels.h"
#include "ui_objectswidget.h"
#include "src/middle/manglobal.h"
#include <src/fend/uidelegates/bucketdelegate.h>

ObjectsWidget::ObjectsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectsWidget)
{
    ui->setupUi(this);
    ui->tableView->setModel(MG->mModels->model());                   // 设置视图(表)内容
//    ui->tableView->setItemDelegate(new BucketDelegate());  // 设置整个代理
    ui->tableView->setItemDelegateForColumn(1,new BucketDelegate());  // 设置某一列的代理，即地区下拉框

    // 设置view的内容
    QStandardItemModel* model = MG->mModels->model();
    QStringList labels;
    labels <<QStringLiteral("桶名称")<< QStringLiteral("地区")<< QStringLiteral("创建时间");
    model->setColumnCount(labels.size());           // 设置列数
    model->setHorizontalHeaderLabels(labels);       // 设置标题

    // 设置列宽度
    ui->tableView->setColumnWidth(0,200);
    ui->tableView->setColumnWidth(1,120);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);     // 设置最后一列占满整个表

    // 隐藏垂直标题
    ui->tableView->verticalHeader()->setHidden(true);

    // 设置鼠标点击进行排序
    ui->tableView->setSortingEnabled(true);
}

ObjectsWidget::~ObjectsWidget()
{
    delete ui;
}
