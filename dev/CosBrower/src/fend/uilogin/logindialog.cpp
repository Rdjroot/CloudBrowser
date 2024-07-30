#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint);        // 去掉默认标题栏

    QPixmap icontt(":/icon/img/icontt.png");
    ui->logoLabel->setPixmap(icontt.scaled(ui->logoLabel->size()));         // 设置图标

    ui->titleLabel->setProperty("style","h3");
    ui->labelRemark->setProperty("style","h4");
    ui->labelSecretID->setProperty("style","h4");
    ui->labelSecretKey->setProperty("style","h4");
    ui->closeButton->setProperty("style","h4");
    ui->btnLogin->setProperty("style","h4");
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

// 单击长按可拖动窗口
void LoginDialog::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton){
        m_start = event->pos();              // 返回相对于父窗口坐标原点的位置
    }
    QDialog::mousePressEvent(event);
}

// 单击长按可拖动窗口
void LoginDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton){
        QPoint targetPos = event->pos()-m_start+pos();
       this->move(targetPos);
    }
    QDialog::mouseMoveEvent(event);
}

void LoginDialog::on_closeButton_clicked()
{
    reject();
}

void LoginDialog::on_btnLogin_clicked()
{
    // 登录信息验证
    if(ui->lineSecretID->text().trimmed() == "zhangsan"
            && ui->lineSecretKey->text().trimmed() == "123")
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this, "登录失败","请检查ID或密码是否正确");
    }
}
