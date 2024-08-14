#include "uimain.h"
#include "src/middle/manglobal.h"
#include "src/middle/signals/mansignals.h"
#include "ui_uimain.h"


UiMain::UiMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiMain)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,3);

    // 关联信号与槽
    // connect(ui->toolwdg,&ToolWidget::buttonClicked, this, &UiMain::onButtonClicked);
    connect(MG->mSignal,&ManSignals::loginSuccess, this, &UiMain::show);
    connect(MG->mSignal, &ManSignals::unLogin, this, &UiMain::onUnLogin);
}

UiMain::~UiMain()
{
    delete ui;
}

// 返回登录窗口
void UiMain::onUnLogin()
{
    // showLoginDialog();
    hide();
}

// 上传处理
void UiMain::onUpload()
{

}

void UiMain::onButtonClicked(const QString &text)
{
    // 根据传过来的文本，设置对应的处理
    if(text == QStringLiteral("上传"))
    {
        onUpload();
    }else if(text == QStringLiteral("退出登录"))
    {
        onUnLogin();
    }
}

