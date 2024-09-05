#include "uibucketstablewidget.h"
#include "src/fend/uidelegates/uitableitemdelegate.h"
#include "ui_uibucketstablewidget.h"
#include "uicreatebucketdialog.h"
#include "src/config/common.h"

#include <QAction>
#include <QJsonObject>
#include <QMessageBox>

#include <src/fend/uicom/uimessagebox.h>

UiBucketsTableWidget::UiBucketsTableWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UiBucketsTableWidget)
{
    ui->setupUi(this);

    ui->tableView->setModel(MG->mModels->modelBuckets());   // 获取桶表
    // 设置列宽度
    ui->tableView->setColumnWidth(0, 200);
    ui->tableView->setColumnWidth(1, 120);
    ui->tableView->horizontalHeader()->setStretchLastSection(true); //设置最后一列占满整个表

    // 隐藏垂直标题
    ui->tableView->verticalHeader()->setHidden(true);

    // 设置鼠标点击排序
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setItemDelegate(new UiTableItemDelegate(ui->tableView));
    ui->btnCreateBucket->setProperty("style_button", "main");   // 给创建桶按钮添加属性

    // 使appid可复制
    ui->appidLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);

    // 初始化表格数据
    connect(MG->mSignal, &ManSignals::bucketsSuccess,
            this, &UiBucketsTableWidget::onBucketsSuccess);

    // 初始化翻页按钮
    ui->widgetPage->setMaxRowList(QList<int>() << 10 << 50 << 100);
    connect(ui->widgetPage, &UiPageWidget::pageNumChanged, this,
            &UiBucketsTableWidget::onPageNumChanged);

    // 添加表格右击（Qt::ActionsContextMenu）上下文选项——删除桶
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction *delAction = new QAction(STR("删除"), this);
    connect(delAction, &QAction::triggered, this,
            &UiBucketsTableWidget::onDelBucket);
    ui->tableView->addAction(delAction);

    // 添加删除桶反馈
    connect(MG->mSignal,&ManSignals::deleteBucketSuccess, this, &UiBucketsTableWidget::onDeleteBucket);
}

UiBucketsTableWidget::~UiBucketsTableWidget()
{
    delete ui;
}

void UiBucketsTableWidget::on_tableView_doubleClicked(const QModelIndex &index)
{
    if(index.column() == 0)     // 单击桶名
    {
        QJsonObject params;
        params["bucketName"] = index.data().toString();
        params["dir"] = "";
        MG->mGate->send(API::OBJECTS::LIST, params);
    }
}

void UiBucketsTableWidget::onBucketsSuccess(const QList<MyBucket> &buckets)
{
    if(!buckets.empty() && appId.isEmpty())
    {
        QString bucketname = buckets[0].name;
        int index = bucketname.indexOf('-');
        QString appid = bucketname.mid(index + 1);
        ui->appidLabel->clear();
        appId = appid;
        ui->appidLabel->setText(STR("当前账户APPID：%1").arg(appId));
    }

    ui->widgetPage->setTotalRow(buckets.size());
    QStandardItemModel *model = MG->mModels->modelBuckets();
    for(int i = 0; i < model->rowCount(); ++i)
    {
        ui->tableView->setRowHeight(i,40);      // 固定行高
    }
}

void UiBucketsTableWidget::onPageNumChanged(int start, int maxLen)
{
    QStandardItemModel *model = MG->mModels->modelBuckets();
    for(int i = 0; i < model->rowCount(); ++i)
    {
        bool hidden = (i < start || i >= (start + maxLen));
        ui->tableView->setRowHidden(i, hidden);         // 隐藏非当前页内容
    }
}


void UiBucketsTableWidget::on_btnCreateBucket_clicked()
{
    // 弹出窗口用于创建存储桶
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

void UiBucketsTableWidget::onDelBucket()
{
    // 获取要删除的条目
    QModelIndex idx = ui->tableView->currentIndex();

    if(idx.isValid()){
        QString name = idx.data().toString();

        // 提示窗口，按键选项设置为中文
        QMessageBox box(
            QMessageBox::Question,
            STR("删除桶"),
            STR("是否确认删除桶【%1】吗？").arg(name),
            QMessageBox::Yes|QMessageBox::No
            );

        box.setButtonText(QMessageBox::Yes, STR("删除"));
        box.setButtonText(QMessageBox::No, STR("取消"));

        int ret = box.exec();
        if(ret == QMessageBox::Yes)
        {
            QJsonObject params;
            params["bucketName"] = name;
            MG->mGate->send(API::BUCKETS::DEL, params);
        }
    }
}

void UiBucketsTableWidget::on_btnRefresh_clicked()
{
    MG->mGate->send(API::BUCKETS::LIST);
}

void UiBucketsTableWidget::onDeleteBucket(const QString& bucketname)
{
    UiMessageBox().showMessage(STR("删除"), STR("成功删除存储桶: %1").arg(bucketname), {STR("确定")},
                               180, 60);
}

