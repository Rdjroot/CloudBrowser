#include "uidownload.h"
#include "src/middle/signals/mansignals.h"
#include "ui_uidownload.h"
#include "src/middle/manglobal.h"
#include "src/config/apis.h"

#include <QJsonValue>

UiDownload::UiDownload(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UiDownload)
{
    ui->setupUi(this);
    initHeader();
    connect(MG->mSignal,&ManSignals::startDownload, this, &UiDownload::onStartDownload);
    connect(MG->mSignal, &ManSignals::downloadProcess, this, &UiDownload::onDownloadProcess);
    connect(MG->mSignal, &ManSignals::downloadSuccess, this, &UiDownload::onDownloadSuccess);
    connect(MG->mSignal, &ManSignals::error, this, &UiDownload::onError);
}

UiDownload::~UiDownload()
{
    delete ui;
}

/**
 * @brief 开始下载
 * @param jobId     任务id
 * @param key       文件
 * @param localPath  本地路径（存储路径）
 * @param total     总大小
 */
void UiDownload::onStartDownload(const QString &jobId, const QString &key, const QString &localPath, qulonglong total)
{
    ui->tableWidget->insertRow(0);
    QTableWidgetItem *item = new QTableWidgetItem(key);
    item->setData(Qt::UserRole, jobId);
    ui->tableWidget->setItem(0, 0, item);
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(localPath));

    UiProgressWidget *bar = new UiProgressWidget();
    bar->setRange(0, total);
    ui->tableWidget->setCellWidget(0, 2, bar);
}

/**
 * @brief 下载中
 * @param jobId
 * @param transferedSize
 * @param totalSize
 */
void UiDownload::onDownloadProcess(const QString &jobId, qulonglong transferedSize, qulonglong totalSize)
{
    Q_UNUSED(totalSize);
    UiProgressWidget* w = findTableWidgetItem(jobId);
    w->setValue(transferedSize);
}

/**
 * @brief 下载完成
 * @param jobId
 */
void UiDownload::onDownloadSuccess(const QString &jobId)
{
    UiProgressWidget* w = findTableWidgetItem(jobId);
    w->setFinished(QString::fromLocal8Bit("下载成功"));
}

/**
 * @brief 处理错误
 * @param api
 * @param msg
 * @param req
 */
void UiDownload::onError(int api, const QString &msg, const QJsonValue &req)
{
    if(api != API::OBJECTS::GET)
        return;

    UiProgressWidget *w = findTableWidgetItem(req["jobId"].toString());
    w->setError(QString::fromLocal8Bit("下载失败"));
    w->setToolTip(msg);
}

/**
 * @brief 查找子窗口item
 * @param jobId 任务id
 * @return  符合的窗口item
 */
UiProgressWidget *UiDownload::findTableWidgetItem(const QString &jobId)
{
    // TODO 这段代码解读
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(i,0);
        QString itemId = item->data(Qt::UserRole).toString();
        if(itemId == jobId)
        {
            return dynamic_cast<UiProgressWidget*>(ui->tableWidget->cellWidget(i,2));
        }
    }
    return nullptr;
}

/**
 * @brief 初始化窗口
 */
void UiDownload::initHeader()
{
    QStringList headers;
    headers << QString::fromLocal8Bit("云端路径")
            << QString::fromLocal8Bit("本地路径")
            << QString::fromLocal8Bit("下载状态");
    // TODO 以下几个属性详读
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(1);
}
