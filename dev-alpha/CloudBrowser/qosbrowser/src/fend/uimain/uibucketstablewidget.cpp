#include "uibucketstablewidget.h"
#include "src/bend/gateway.h"
#include "src/middle/manglobal.h"
#include "src/middle/manmodels.h"
#include "src/middle/signals/mansignals.h"
#include "ui_uibucketstablewidget.h"
#include "uicreatebucketdialog.h"
#include "src/config/apis.h"

#include <QAction>
#include <QJsonObject>
#include <QMessageBox>

UiBucketsTableWidget::UiBucketsTableWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UiBucketsTableWidget)
{
    ui->setupUi(this);

    ui->tableView->setModel(MG->mModels->modelBuckets());
    // 设置列宽度
    ui->tableView->setColumnWidth(0, 200);
    ui->tableView->setColumnWidth(1, 120);
    ui->tableView->horizontalHeader()->setStretchLastSection(true); //设置最后一列占满整个表
    // 隐藏垂直标题
    ui->tableView->verticalHeader()->setHidden(true);
    // 设置鼠标点击排序
    ui->tableView->setSortingEnabled(true);

    // 初始化表格数据
    connect(MG->mSignal, &ManSignals::bucketsSuccess,
            this, &UiBucketsTableWidget::onBucketsSuccess);

    // 初始化翻页按钮
    ui->widgetPage->setMaxRowList(QList<int>() << 10 << 50 << 100);
    connect(ui->widgetPage, &UiPageWidget::pageNumChanged, this,
            &UiBucketsTableWidget::onPageNumChanged);

    // 添加表格右击（Qt::ActionsContextMenu）上下文选项——删除桶
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction *delAction = new QAction(QString::fromLocal8Bit("删除"), this);
    connect(delAction, &QAction::triggered, this,
            &UiBucketsTableWidget::onDelBucket);
    ui->tableView->addAction(delAction);
}

UiBucketsTableWidget::~UiBucketsTableWidget()
{
    delete ui;
}

void UiBucketsTableWidget::on_tableView_doubleClicked(const QModelIndex &index)
{
    if(index.column() == 0)
    {
        QJsonObject params;
        params["bucketName"] = index.data().toString();
        params["dir"] = "";
        MG->mGate->send(API::OBJECTS::LIST, params);
    }
}

void UiBucketsTableWidget::onBucketsSuccess(const QList<MyBucket> &buckets)
{
    ui->widgetPage->setTotalRow(buckets.size());
}

void UiBucketsTableWidget::onPageNumChanged(int start, int maxLen)
{
    QStandardItemModel *model = MG->mModels->modelBuckets();
    for(int i = 0; i < model->rowCount(); ++i)
    {
        bool hidden = (i < start || i >= (start + maxLen));
        ui->tableView->setRowHidden(i, hidden);
    }
}


void UiBucketsTableWidget::on_btnCreateBucket_clicked()
{
    UiCreateBucketDialog dialog(this);
    int ret = dialog.exec();
    if (ret == QDialog::Accepted) {
        MyBucket bucket = dialog.getBucket();
        if (bucket.isValid()) {
            QJsonObject params;
            params["bucketName"] = bucket.name;
            params["location"] = bucket.location;
            MG->mGate->send(API::BUCKETS::PUT, params);
        }
    }
}

/**
 * @brief 删除存储桶
 */
void UiBucketsTableWidget::onDelBucket()
{
    QModelIndex idx = ui->tableView->currentIndex();

    if(idx.isValid()){
        QString name = idx.data().toString();

        // 提示窗口，按键选项设置为中文
        QMessageBox box(
            QMessageBox::Question,
            QString::fromLocal8Bit("删除桶"),
            QString::fromLocal8Bit("是否确认删除桶【%1】吗？").arg(name),
            QMessageBox::Yes|QMessageBox::No
            );

        box.setButtonText(QMessageBox::Yes, QString::fromLocal8Bit("删除"));
        box.setButtonText(QMessageBox::No, QString::fromLocal8Bit("取消"));

        int ret = box.exec();
        if(ret == QMessageBox::Yes)
        {
            QJsonObject params;
            params["bucketName"] = name;
            MG->mGate->send(API::BUCKETS::DEL, params);
        }
    }
}

/**
 * @brief 刷新存储桶
 */
void UiBucketsTableWidget::on_btnRefresh_clicked()
{
    MG->mGate->send(API::BUCKETS::LIST);
}

