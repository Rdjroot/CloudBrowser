﻿#include "uimain.h"
#include "src/fend/uicom/uimessagebox.h"
#include "src/middle/manglobal.h"
#include "src/middle/signals/mansignals.h"
#include "ui_uimain.h"
#include "src/config/common.h"
#include <QPushButton>


UiMain::UiMain(QWidget *parent) :
    UiQosDialog(parent),
    ui(new Ui::UiMain)
{
    ui->setupUi(body());
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,4);

    m_transfer = new UiTransfer(this);
    // 右上角图标
    UiPushButton* transBtn = addButton(GLOBAL::PATH::TRANS, GLOBAL::PATH::TRANS_HOVER);
    connect(transBtn, &UiPushButton::clicked,this, &UiMain::showTransfer);
    UiPushButton* quitBtn = addButton(GLOBAL::PATH::QUIT,GLOBAL::PATH::QUIT_HOVER);
    connect(quitBtn, &UiPushButton::clicked,MG->mSignal, &ManSignals::unLogin);

    addTitleLine();             // 右上角分割线

    // 缩放按钮以及标题
    addMinButton(GLOBAL::PATH::MIN_PATH, GLOBAL::PATH::MIN_HOVER_PATH);
    addMaxButton(GLOBAL::PATH::MAX_PATH1,GLOBAL::PATH::MAX_HOVER_PATH,GLOBAL::PATH::NORMAL_PATH,GLOBAL::PATH::NORMAL_HOVER_PATH);
    setTitle(QString::fromLocal8Bit("Cloud Browser"));
    resize(1080,640);
    setKeyDisabled();  // 禁用esc或回车，导致窗口关闭

    // 关联信号与槽
    connect(MG->mSignal,&ManSignals::loginSuccess, this, &UiMain::show);
    connect(MG->mSignal, &ManSignals::unLogin, this, &UiMain::onUnLogin);
    connect(MG->mSignal, &ManSignals::bucketsSuccess, this, &UiMain::onBucketsSuccess);
    connect(MG->mSignal, &ManSignals::objectsSuccess, this, &UiMain::onObjectsSuccess);
    connect(MG->mSignal, &ManSignals::error, this, &UiMain::onError);

}

UiMain::~UiMain()
{
    delete ui;
    if(m_transfer != nullptr)
        delete m_transfer;
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
    m_transfer->show();
}

/**
 * @brief 弹出窗口提示报错
 * @param api   接口
 * @param msg   信息
 * @param req   请求
 */
void UiMain::onError(int api, const QString &msg, const QJsonValue &req)
{
    Q_UNUSED(req);
    if(isVisible() && api > API::BUCKETS::BASE)
    {
        UiMessageBox().showMessage(STR("错误"), msg);
    }
}

