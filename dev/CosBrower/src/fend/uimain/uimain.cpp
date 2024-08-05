#include "uimain.h"
#include "ui_uimain.h"

UiMain::UiMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiMain)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,4);

    connect(ui->toolwdg,&ToolWidget::buttonClicked, this, &UiMain::onButtonClicked);
}

UiMain::~UiMain()
{
    delete ui;
    if(m_loginDialog)
    {
        delete m_loginDialog;
    }
}

// 登录窗口
void UiMain::showLoginDialog()
{
    if(m_loginDialog == nullptr)
    {
        m_loginDialog = new LoginDialog();
        m_loginDialog->updateLoginInfo();
        connect(m_loginDialog,&LoginDialog::accepted,this,&UiMain::show);
        connect(ui->toolwdg,&ToolWidget::quitLogin,this,&UiMain::showLoginDialog);
    }
    hide();
    m_loginDialog->show();
}

// 返回登录窗口
void UiMain::onUnLogin()
{
    showLoginDialog();
}

void UiMain::onUpload()
{

}

void UiMain::onButtonClicked(const QString &text)
{
    // 根据传过来的文本，设置对应的处理
    if(text == QString("上传"))
    {
        onUpload();
    }else if(text == QString("退出登录"))
    {
        onUnLogin();
    }
}

