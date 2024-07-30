#include "uimain.h"
#include "ui_uimain.h"

UiMain::UiMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiMain)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,4);
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
        connect(m_loginDialog,&LoginDialog::accepted,this,&UiMain::show);
        connect(ui->toolwdg,&ToolWidget::quitLogin,this,&UiMain::showLoginDialog);
    }
    hide();
    m_loginDialog->show();
}
