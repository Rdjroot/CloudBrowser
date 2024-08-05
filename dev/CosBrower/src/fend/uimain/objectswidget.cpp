#include "objectswidget.h"
#include "ui_objectswidget.h"

#include <src/fend/uidelegates/bucketdelegate.h>

ObjectsWidget::ObjectsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectsWidget)
{
    ui->setupUi(this);
    ui->tableView->setModel(MB->model());
//    ui->tableView->setItemDelegate(new BucketDelegate());  // 设置整个代理
    ui->tableView->setItemDelegateForColumn(1,new BucketDelegate());      // 设置某一列的代理

    // 设置标题内容
    QStandardItemModel* model = MB->model();
    QStringList labels;
    labels << "桶名称"<<"地区"<<"创建时间";
    model->setColumnCount(labels.size());
    model->setHorizontalHeaderLabels(labels);       // 设置标题

    // 设置列宽度
    ui->tableView->setColumnWidth(0,200);
    ui->tableView->setColumnWidth(1,120);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);     // 设置最后一列占满整个表

    // 隐藏垂直标题
    ui->tableView->verticalHeader()->setHidden(true);

    // 设置鼠标点击排序
    ui->tableView->setSortingEnabled(true);
}

ObjectsWidget::~ObjectsWidget()
{
    delete ui;
}
