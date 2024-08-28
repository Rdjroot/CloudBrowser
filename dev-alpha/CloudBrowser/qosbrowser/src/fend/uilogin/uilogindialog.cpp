#include "uilogindialog.h"
#include "src/bend/gateway.h"
#include "src/bend/man/mandb.h"
#include "src/middle/manglobal.h"
#include "ui_uilogindialog.h"
#include "src/config/apis.h"

#include <QCompleter>
#include <QJsonObject>
#include <QMessageBox>

#include <src/middle/signals/mansignals.h>

UiLoginDialog::UiLoginDialog(QWidget *parent)
    : UiQosDialog(parent)
    , ui(new Ui::UiLoginDialog)
{
    ui->setupUi(body());
    setTitle("登录");

    ui->btnLogin->setDefault(true);     // 默认enter

    // 设置控件的属性（供qss设定）
    ui->labelLoginName->setProperty("style","h5");
    ui->labelSecretID->setProperty("style","h5");
    ui->labelSecretKey->setProperty("style","h5");
    ui->labelRemark->setProperty("style","h5");

    ui->btnLogin->setProperty("style","h5");
    ui->btnLogin->setProperty("style_button","main");

    connect(ui->btnLogin, &UiPushButton::clicked, this, &UiLoginDialog::onBtnLoginClicked);

    connect(MG->mSignal, &ManSignals::loginSuccess, this, &UiLoginDialog::onLoginSucceed);
    connect(MG->mSignal, &ManSignals::unLogin, this, &UiLoginDialog::show);
    connect(MG->mSignal, &ManSignals::error, this, &UiLoginDialog::onLoginError);
    complementLoginInfo();              // 登录信息补全

    resize(400,450);
}

UiLoginDialog::~UiLoginDialog()
{
    delete ui;
}

// 通过登录名补全
void UiLoginDialog::complementLoginInfo()
{
    QStringList words = MG->mDb->loginNameList();
    QCompleter* completer = new QCompleter(words);
    ui->lineLoginName->setCompleter(completer);

    // 如果从下拉框中选中的话
    connect(completer, static_cast<void (QCompleter::*)(const QString&)>(&QCompleter::activated),
            [&](const QString& name){
                LoginInfo info =  MG->mDb->loginInfoByName(name);
                ui->lineSecretID->setText(info.secret_id);
                ui->lineSecretKey->setText(info.secret_key);
                ui->lineRemark->setText(info.remark);
                ui->saveSection->setChecked(true);
            });
}

// 登录按键
void UiLoginDialog::onBtnLoginClicked()
{
    QJsonObject params;
    params["secretId"] = ui->lineSecretID->text().trimmed();
    params["secretKey"] = ui->lineSecretKey->text().trimmed();
    // 进入主界面
    MG->mGate->send(API::LOGIN::NORMAL, params);
}

// 登录成功
void UiLoginDialog::onLoginSucceed()
{
    if(ui->saveSection->isChecked())
    {
        // 保存登录信息
         MG->mDb->saveLoginInfo(
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
        MG->mDb->removeLoginInfo(ui->lineSecretID->text());
    }
    accept();           // 发送accept信号
}

void UiLoginDialog::onLoginError(int api, const QString &msg, const QJsonValue &req)
{
    Q_UNUSED(req)
    if(api != API::LOGIN::NORMAL)
        return;

    QMessageBox::warning(this,QString::fromUtf8("警告"),QString::fromUtf8("登录失败: %1").arg(msg));
}
