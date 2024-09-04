#include "uiobjectstablewidget.h"
#include "src/fend/uidelegates/uitableitemdelegate.h"
#include "ui_uiobjectstablewidget.h"
#include "src/config/common.h"

#include <QFileDialog>
#include <QJsonObject>
#include <QMessageBox>
#include <src/helper/filehelper.h>
#include <src/fend/uicom/uimessagebox.h>

UiObjectsTableWidget::UiObjectsTableWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UiObjectsTableWidget)
{
    ui->setupUi(this);
    ui->btnBuckets->setProperty("style_button", "main");
    ui->tableView->setModel(MG->mModels->modelObjects());

    // 设置列宽度
    ui->tableView->setColumnWidth(0, 200);
    ui->tableView->setColumnWidth(1, 120);
    ui->tableView->horizontalHeader()->setStretchLastSection(
        true); // 设置最后一列占满整个表

    // 隐藏垂直标题, 也就是最左侧的序列号
    ui->tableView->verticalHeader()->setHidden(true);

    // 设置鼠标点击排序，以及view代理
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setItemDelegate(new UiTableItemDelegate(ui->tableView));

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

void UiObjectsTableWidget::onObjectsSuccess(const QList<MyObject> &objects)
{
    QString path = MG->mCloud->currentBucketName() + "/" + MG->mCloud->currentDir();
    ui->widgetBread->setPath(path);
    ui->widgetPage->setTotalRow(objects.size());
    QStandardItemModel *model = MG->mModels->modelObjects();
    for (int i = 0; i < model->rowCount(); ++i) {
        ui->tableView->setRowHeight(i, 40);
    }
}

void UiObjectsTableWidget::onPageNumChanged(int start, int maxLen)
{
    QStandardItemModel *model = MG->mModels->modelObjects();
    for(int i = 0; i < model->rowCount();i++)
    {
        bool hidden = (i < start || (i >= start + maxLen));
        ui->tableView->setRowHidden(i, hidden);
    }
}

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

void UiObjectsTableWidget::on_btnRefresh_clicked()
{
    onPathChanged(ui->widgetBread->currentPath());
}

void UiObjectsTableWidget::on_btnUpload_clicked()
{
    static QString lastDir = "./";
    QString filePath = QFileDialog::getOpenFileName(
        this, STR("上传文件"), lastDir
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
        params["key"] = MG->mCloud->currentDir() + info.fileName();
        params["localPath"] = filePath;

        MG->mGate->send(API::OBJECTS::PUT,params);
        lastDir = info.dir().absolutePath();        // 记忆上次打开的本地目录
        // 关联传输列表
        emit MG->mSignal->startUpload(jobId, key, filePath);
    }
}

void UiObjectsTableWidget::onUploadSuccess(const QString &jobId)
{
    Q_UNUSED(jobId);
    on_btnRefresh_clicked();
    UiMessageBox().showMessage(STR("上传"), STR("上传文件成功"), {STR("确定")},
                               180, 60);
}

void UiObjectsTableWidget::on_btnDownload_clicked()
{
    QModelIndex idx = ui->tableView->currentIndex();
    if(!idx.isValid())
    {
        UiMessageBox().showMessage(STR("下载"), STR("请选择要下载的文件"), {STR("确定")},
                                   180, 60);
        return;
    }

    MyObject obj = idx.data(Qt::UserRole).value<MyObject>();
    if (obj.isDir()) {
        UiMessageBox().showMessage(STR("下载"), STR("只能选择文件进行下载"), {STR("确定")},
                                   180, 60);
        return;
    }

    QString name = idx.data().toString();
    static QString lastDir = "./";
    QString filePath = QFileDialog::getSaveFileName(
        this, STR("下载文件"),FileHelper::joinPath(lastDir, name)
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
    lastDir = info.dir().absolutePath();
    emit MG->mSignal->startDownload(jobId, key, filePath, obj.size);
}

void UiObjectsTableWidget::onDownloadSuccess(const QString &jobId)
{
    Q_UNUSED(jobId);
    UiMessageBox().showMessage(STR("下载"), STR("下载文件成功"), {STR("确定")},
                               180, 60);
}
