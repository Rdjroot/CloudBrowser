#include "uiobjectstablewidget.h"
#include "src/bend/gateway.h"
#include "src/bend/man/mancloud.h"
#include "src/middle/manglobal.h"
#include "src/middle/manmodels.h"
#include "src/middle/signals/mansignals.h"
#include "ui_uiobjectstablewidget.h"
#include "src/config/apis.h"

#include <QFileDialog>
#include <QJsonObject>
#include <QMessageBox>

#include <src/helper/filehelper.h>

// BUG 没有实现进入目录
UiObjectsTableWidget::UiObjectsTableWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UiObjectsTableWidget)
{
    ui->setupUi(this);
    ui->tableView->setModel(MG->mModels->modelObjects());

    // 设置列宽度
    ui->tableView->setColumnWidth(0, 200);
    ui->tableView->setColumnWidth(1, 120);
    ui->tableView->horizontalHeader()->setStretchLastSection(
        true); // 设置最后一列占满整个表

    // 隐藏垂直标题, 也就是最左侧的序列号
    ui->tableView->verticalHeader()->setHidden(true);

    // 设置鼠标点击排序
    ui->tableView->setSortingEnabled(true);

    // 关联对象数据显示
    connect(MG->mSignal, &ManSignals::objectsSuccess, this,
            &UiObjectsTableWidget::onObjectsSuccess);

    // 初始化翻页按钮
    ui->widgetPage->setMaxRowList(QList<int>() << 5 << 10 << 20);
    connect(ui->widgetPage, &UiPageWidget::pageNumChanged, this, &UiObjectsTableWidget::onPageNumChanged);

    // 关联面包屑导航
    connect(ui->widgetBread, &UiBreadWidget::pathChanged, this, &UiObjectsTableWidget::onPathChanged);

    // 关联上传/下载成功信号
    connect(MG->mSignal, &ManSignals::uploadSuccess, this, &UiObjectsTableWidget::onUploadSuccess);
    connect(MG->mSignal, &ManSignals::downloadSuccess, this, &UiObjectsTableWidget::onDownloadSuccess);
}

UiObjectsTableWidget::~UiObjectsTableWidget()
{
    delete ui;
}

void UiObjectsTableWidget::on_btnBuckets_clicked()
{
    MG->mGate->send(API::BUCKETS::LIST);
}


void UiObjectsTableWidget::on_tableView_doubleClicked(const QModelIndex &index)
{
    // 将index中userRole中的数据（原本是QVariant）转换成<T>的数据返回
    MyObject obj = index.data(Qt::UserRole).value<MyObject>();

    if(obj.isDir())
    {
        QJsonObject params;
        params["bucketName"] = MG->mCloud->currentBucketName();
        params["dir"] = obj.key;
        MG->mGate->send(API::OBJECTS::LIST, params);
    }
}

/**
 * @brief 设置文件条目和目录
 * @param objects
 */
void UiObjectsTableWidget::onObjectsSuccess(const QList<MyObject> &objects)
{
    QString path = MG->mCloud->currentBucketName() + "/" + MG->mCloud->currentDir();
    ui->widgetBread->setPath(path);
    ui->widgetPage->setTotalRow(objects.size());
}

/**
 * @brief 翻页
 * @param start
 * @param maxLen
 */
void UiObjectsTableWidget::onPageNumChanged(int start, int maxLen)
{
    QStandardItemModel *model = MG->mModels->modelObjects();
    for(int i = 0; i < model->rowCount();i++)
    {
        bool hidden = (i < start || (i >= start + maxLen));
        ui->tableView->setRowHidden(i, hidden);
    }
}

/**
 * @brief 目录更替
 * @param newPath
 */
void UiObjectsTableWidget::onPathChanged(const QString &newPath)
{
    // newPath=file-xxxxxxxxx/test/bll
    // 需要将newPath 转化为 test/bll/
    QString key = newPath + "/";
    key = key.mid(key.indexOf("/") + 1);

    QJsonObject params;
    params["bucketName"] = MG->mCloud->currentBucketName();
    params["dir"] = key;
    MG->mGate->send(API::OBJECTS::LIST, params);
}

/**
 * @brief 刷新页面
 */
void UiObjectsTableWidget::on_btnRefresh_clicked()
{
    onPathChanged(ui->widgetBread->currentPath());
}

/**
 * @brief 上传文件
 */
void UiObjectsTableWidget::on_btnUpload_clicked()
{
    static QString lastDir = "./";
    QString filePath = QFileDialog::getOpenFileName(
        this, QString::fromLocal8Bit("上传文件"),lastDir
        );

    QFileInfo info(filePath);

    if(info.isFile() && info.exists())
    {
        // 创建全球唯一的uuid
        QString jobId = QUuid::createUuid().toString();

        filePath = filePath.replace("\\","/");
        QJsonObject params;
        QString key = MG->mCloud->currentDir() + info.fileName();
        params["jobId"] = jobId;
        params["bucketName"] = MG->mCloud->currentBucketName();
        params["key"] = key;
        params["localPath"] = filePath;
        qDebug()<< QString("1!!!! filePath is %1.").arg(filePath);
        MG->mGate->send(API::OBJECTS::PUT,params);
    }
}

/**
 * @brief 上传成功
 * @param jobId 任务id
 */
void UiObjectsTableWidget::onUploadSuccess(const QString &jobId)
{
    Q_UNUSED(jobId);
    on_btnRefresh_clicked();
    showMessage(QString::fromLocal8Bit("上传"),QString::fromLocal8Bit("上传文件成功"));
}

/**
 * @brief 下载文件
 * @param jobId 任务id
 */
void UiObjectsTableWidget::on_btnDownload_clicked()
{
    QModelIndex idx = ui->tableView->currentIndex();
    if(!idx.isValid())
    {
        showMessage(
            QString::fromLocal8Bit("下载"),
            QString::fromLocal8Bit("请选择要下载的文件"));
        return;
    }

    MyObject obj = idx.data(Qt::UserRole).value<MyObject>();
    if (obj.isDir()) {
        showMessage(
            QString::fromLocal8Bit("下载"),
            QString::fromLocal8Bit("只能选择文件进行下载"));
        return;
    }

    QString name = idx.data().toString();
    static QString lastDir = "./";
    QString filePath = QFileDialog::getSaveFileName(
        this, QString::fromLocal8Bit("下载文件"),FileHelper::joinPath(lastDir, name)
        );

    if(filePath.isEmpty())
        return;

    QFileInfo info(filePath);
    QString jobId = QUuid::createUuid().toString();

    filePath = filePath.replace("\\","/");
    QJsonObject params;
    QString key = MG->mCloud->currentDir() + name;
    params["jobId"] = jobId;
    params["bucketName"] = MG->mCloud->currentBucketName();
    params["key"] = key;
    params["localPath"] = filePath;
    MG->mGate->send(API::OBJECTS::GET, params);
}

/**
 * @brief 下载成功
 * @param jobId 任务id
 */
void UiObjectsTableWidget::onDownloadSuccess(const QString &jobId)
{
    Q_UNUSED(jobId);
    showMessage(QString::fromLocal8Bit("下载"),QString::fromLocal8Bit("下载文件成功"));
}

/**
 * @brief 公有函数，显示提示（上传/下载）信息
 * @param title  box标题
 * @param info box内容
 */
void UiObjectsTableWidget::showMessage(const QString &title, const QString &info)
{
    // QMessageBox box(QMessageBox::Information, title, info, QMessageBox::Ok);
    // box.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确定"));
    // box.exec();
}

