#include "uimain.h"
#include "src/fend/uicom/uimessagebox.h"
#include "src/middle/manglobal.h"
#include "src/middle/signals/mansignals.h"
#include "ui_uimain.h"
#include "src/config/global.h"
#include "src/config/apis.h"
#include <QPushButton>


UiMain::UiMain(QWidget *parent) :
    UiQosDialog(parent),
    ui(new Ui::UiMain)
{
    ui->setupUi(body());
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,4);

    // 右上角图标
    QPushButton* transBtn = addButton(GLOBAL::PATH::TRANS, GLOBAL::PATH::TRANS_HOVER);
    connect(transBtn, &QPushButton::clicked,this, &UiMain::showTransfer);
    QPushButton* quitBtn = addButton(GLOBAL::PATH::QUIT,GLOBAL::PATH::QUIT_HOVER);
    connect(quitBtn, &QPushButton::clicked,MG->mSignal, &ManSignals::unLogin);

    addTitleLine();             // 右上角分割线

    // 缩放按钮以及标题
    addMinButton(GLOBAL::PATH::MIN_PATH, GLOBAL::PATH::MIN_HOVER_PATH);
    addMaxButton(GLOBAL::PATH::MAX_PATH,GLOBAL::PATH::MAX_HOVER_PATH,GLOBAL::PATH::NORMAL_PATH,GLOBAL::PATH::NORMAL_HOVER_PATH);
    setTitle(QString::fromLocal8Bit("Cloud Browser"));
    resize(1080,640);
    setKeyDisabled();  // 禁用esc或回车，导致窗口关闭

    // 关联信号与槽
    connect(MG->mSignal,&ManSignals::loginSuccess, this, &UiMain::show);
    connect(MG->mSignal, &ManSignals::unLogin, this, &UiMain::onUnLogin);
    connect(MG->mSignal, &ManSignals::bucketsSuccess, this, &UiMain::onBucketsSuccess);
    connect(MG->mSignal, &ManSignals::objectsSuccess, this, &UiMain::onObjectsSuccess);
    connect(MG->mSignal, &ManSignals::error, this, &UiMain::onError);
    m_transfer = new UiTransfer(this);
}

UiMain::~UiMain()
{
    delete ui;
}

// 返回登录窗口
void UiMain::onUnLogin()
{
    hide();
}

void UiMain::onBucketsSuccess(const QList<MyBucket> &buckets)
{
    Q_UNUSED(buckets);
    ui->stackedWidget->setCurrentIndex(0);      // 设置窗口更替
}

void UiMain::onObjectsSuccess(const QList<MyObject> &objcets)
{
    Q_UNUSED(objcets);
    ui->stackedWidget->setCurrentIndex(1);
}

void UiMain::showTransfer()
{
    if(!m_transfer)
    {
        m_transfer = new UiTransfer(this);
    }
    m_transfer->show();
}

void UiMain::onError(int api, const QString &msg, const QJsonValue &req)
{
    if(isVisible() && api > API::BUCKETS::BASE)
    {
        UiMessageBox().showMessage(QString::fromLocal8Bit("错误"), msg);
    }
}


