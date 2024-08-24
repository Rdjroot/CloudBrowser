#include "uiupload.h"
#include "src/middle/manglobal.h"
#include "src/middle/signals/mansignals.h"
#include "ui_uiupload.h"
#include "src/config/apis.h"
#include <QFileInfo>
#include <QJsonValue>

UiUpload::UiUpload(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UiUpload)
{
    ui->setupUi(this);
    initHeader();
    connect(MG->mSignal, &ManSignals::startUpload, this, &UiUpload::onStartUpload);
    connect(MG->mSignal, &ManSignals::uploadProcess, this, &UiUpload::onUploadProcess);
    connect(MG->mSignal, &ManSignals::uploadSuccess, this, &UiUpload::onUploadSuccess);
    connect(MG->mSignal, &ManSignals::error, this, &UiUpload::onError);
}

UiUpload::~UiUpload()
{
    delete ui;
}

/**
 * @brief 开始上传
 * @param jobId
 * @param key
 * @param localPath
 */
void UiUpload::onStartUpload(const QString &jobId, const QString &key, const QString &localPath)
{
    ui->tableWidget->insertRow(0);
    QTableWidgetItem* item = new QTableWidgetItem(key);
    item->setData(Qt::UserRole, jobId);
    ui->tableWidget->setItem(0, 0, item);
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(localPath));

    QFileInfo info(localPath);
    UiProgressWidget *bar = new UiProgressWidget();
    bar->setRange(0, info.size());
    ui->tableWidget->setCellWidget(0, 2, bar);
}

/**
 * @brief 上传中
 * @param jobId
 * @param transferedSize
 * @param totalSize
 */
void UiUpload::onUploadProcess(const QString &jobId, qulonglong transferedSize, qulonglong totalSize)
{
    UiProgressWidget* w = findTableWidgetItem(jobId);
    w->setValue(transferedSize);
}

/**
 * @brief 上传成功
 * @param jobId
 */
void UiUpload::onUploadSuccess(const QString &jobId)
{
    UiProgressWidget* w = findTableWidgetItem(jobId);
    w->setFinished(QString::fromLocal8Bit("上传成功"));
}

/**
 * @brief 上传出错
 * @param api
 * @param msg
 * @param req
 */
void UiUpload::onError(int api, const QString &msg, const QJsonValue &req)
{
    if (api != API::OBJECTS::PUT)
        return;
    UiProgressWidget* w = findTableWidgetItem(req["jobId"].toString());
    w->setError(QString::fromLocal8Bit("上传失败"));
    w->setToolTip(msg);
}

UiProgressWidget *UiUpload::findTableWidgetItem(const QString &jobId)
{
    for (int i  = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QTableWidgetItem* item = ui->tableWidget->item(i, 0);
        QString itemId = item->data(Qt::UserRole).toString();
        if (itemId == jobId)
        {
            return dynamic_cast<UiProgressWidget*>(ui->tableWidget->cellWidget(i, 2));
        }
    }
    return nullptr;
}

/**
 * @brief 初始化窗口
 */
void UiUpload::initHeader()
{
    QStringList headers;
    headers << QString::fromLocal8Bit("云端路径")
            << QString::fromLocal8Bit("本地路径")
            << QString::fromLocal8Bit("上传状态");
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(1);
}
