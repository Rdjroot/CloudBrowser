#include "src/bend/gateway.h"
#include "src/middle/signals/mansignals.h"
#include "logindialog.h"
#include "ui_logindialog.h"
#include "src/bend/man/mandb.h"
#include "src/config/apis.h"
#include <QCompleter>
#include <QJsonObject>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint);        // 去掉默认标题栏

    // 设置图标
    QPixmap icontt(":/static/img/icontt.png");
    ui->logoLabel->setPixmap(icontt.scaled(ui->logoLabel->size()));

    // 设置控件的属性（供qss设定）
    ui->titleLabel->setProperty("style","h3");
    ui->labelLoginName->setProperty("style","h4");
    ui->labelRemark->setProperty("style","h4");
    ui->labelSecretID->setProperty("style","h4");
    ui->labelSecretKey->setProperty("style","h4");
    ui->closeButton->setProperty("style","h4");
    ui->btnLogin->setProperty("style","h4");

    connect(MS, &ManSignals::loginSuccess, this, &LoginDialog::onLoginSucceed);
    connect(MS, &ManSignals::unLogin, this, &LoginDialog::show);
    connect(MS, &ManSignals::error, this, &LoginDialog::onLoginError);
    complementLoginInfo();              // 登录信息补全
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

// 通过登录名补全
void LoginDialog::complementLoginInfo()
{
    QStringList words = MDB->loginNameList();
    QCompleter* completer = new QCompleter(words);
    ui->lineLoginName->setCompleter(completer);

    // 如果从下拉框中选中的话
    connect(completer, static_cast<void (QCompleter::*)(const QString&)>(&QCompleter::activated),
            [&](const QString& name){
                LoginInfo info = MDB->loginInfoByName(name);
                ui->lineSecretID->setText(info.secret_id);
                ui->lineSecretKey->setText(info.secret_key);
                ui->lineRemark->setText(info.remark);
                ui->saveSection->setChecked(true);
            });
}

// 获取单击时的起始位置,重写函数
void LoginDialog::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton){
        m_start = event->pos();              // 返回相对于父窗口坐标原点的位置
    }
    QDialog::mousePressEvent(event);        // 在最后要反调父函数
}

// 单击长按可拖动窗口，重写函数
void LoginDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton){
        QPoint targetPos = event->pos()-m_start+pos();  // 目标位置
        this->move(targetPos);                  // 窗口移动
    }
    QDialog::mouseMoveEvent(event);     // 在最后要反调父函数
}

void LoginDialog::on_closeButton_clicked()
{
    reject();           //关闭窗口
}

// 登录按键
void LoginDialog::on_btnLogin_clicked()
{
    QJsonObject params;
    params["secretId"] = ui->lineSecretID->text().trimmed();
    params["secretKey"] = ui->lineSecretKey->text().trimmed();
    // TODO 这里后续应该进行主界面
    GW->send(API::LOGIN::NORMAL, params);

}

// 登录成功
void LoginDialog::onLoginSucceed()
{
    accept();           // 发送accept信号

    if(ui->saveSection->isChecked())
    {
        // 保存登录信息
        MDB->saveLoginInfo(
            ui->lineLoginName->text(),
            ui->lineSecretID->text(),
            ui->lineSecretKey->text(),
            ui->lineRemark->text()
        );
        complementLoginInfo();
    }
    else
    {
        // 删除登录信息
        MDB->removeLoginInfo(ui->lineSecretID->text());
    }
}

void LoginDialog::onLoginError(int api, const QString &msg)
{
    if(api != API::LOGIN::NORMAL)
        return;

    QMessageBox::warning(this,QString::fromUtf8("警告"),QString::fromUtf8("登录失败: %1").arg(msg));
}
