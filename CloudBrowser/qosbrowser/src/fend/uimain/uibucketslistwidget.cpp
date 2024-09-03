#include "uibucketslistwidget.h"
#include "src/bend/gateway.h"
#include "src/middle/manglobal.h"
#include "src/middle/manmodels.h"
#include "src/middle/signals/mansignals.h"
#include "ui_uibucketslistwidget.h"

#include "src/config/apis.h"
#include <QJsonObject>

UiBucketsListWidget::UiBucketsListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiBucketsListWidget)
{
    ui->setupUi(this);
    ui->listView->setModel(MG->mModels->modelBuckets());        // 设置桶视图

    // 关联信号中心和当前界面
    connect(MG->mSignal, &ManSignals::bucketsSuccess,
            this, &UiBucketsListWidget::onBucketSuccess);

    // 搜索框引导和完善
    connect(ui->lineEdit, &UiComboLine::itemSelected, this, &UiBucketsListWidget::showBucketObjects);
    connect(ui->lineEdit, &UiComboLine::textEdited, this, &UiBucketsListWidget::onTextEdited);
}

UiBucketsListWidget::~UiBucketsListWidget()
{
    delete ui;
}

void UiBucketsListWidget::onBucketSuccess(const QList<MyBucket> &buckets)
{
    QStringList words;
    for(const auto& bucket:qAsConst(buckets))
    {
        words.append(bucket.name);
    }
    ui->lineEdit->setWords(words);      // comboline设置关键词
}

void UiBucketsListWidget::on_listView_doubleClicked(const QModelIndex &index)
{
    showBucketObjects(index.data().toString());
}

void UiBucketsListWidget::showBucketObjects(const QString &bucketName)
{
    QJsonObject params;
    params["bucketName"] = bucketName;
    params["dir"] = "";
    MG->mGate->send(API::OBJECTS::LIST, params);    // 获取对象列表
}

void UiBucketsListWidget::onTextEdited(const QString &text)
{
    QStandardItemModel *model = MG->mModels->modelBuckets();
    for(int i = 0; i<model->rowCount();++i)
    {
        bool hidden = !(model->index(i,0).data().toString().contains(text));
        ui->listView->setRowHidden(i, hidden);   // 隐藏不符合的条目
    }
}

