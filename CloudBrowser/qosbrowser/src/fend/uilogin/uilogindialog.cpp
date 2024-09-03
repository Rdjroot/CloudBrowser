#include "uilogindialog.h"
#include "src/config/common.h"
#include "src/bend/man/mandb.h"
#include "ui_uilogindialog.h"

#include <QCompleter>
#include <QJsonObject>
#include <QMessageBox>

#include <src/middle/signals/mansignals.h>

#include <src/fend/uicom/uimessagebox.h>

UiLoginDialog::UiLoginDialog(QWidget *parent)
    : UiQosDialog(parent)
    , ui(new Ui::UiLoginDialog)
{
    ui->setupUi(body());
    setTitle(STR("CloudBrowser 登录"));

    ui->btnLogin->setDefault(true);     // 默认enter为敲击登录按钮

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
    updateLoginInfo();         // 初始化登录信息

    resize(400,450);
    connect(MG->mDb,&ManDB::errorOccurred,this, &UiLoginDialog::dealDBError);
}

UiLoginDialog::~UiLoginDialog()
{
    delete ui;
}

void UiLoginDialog::updateLoginInfo()
{
    // 获取数据库中所有登录名
    QStringList words = MG->mDb->loginNameList();
    ui->lineLoginName->setWords(words);

    // 补全登录栏
    connect(ui->lineLoginName, &UiComboLine::itemSelected,
            [=](const QString &name) {
                LoginInfo info = MG->mDb->loginInfoByName(name);
                ui->lineSecretID->setText(info.secret_id);
                ui->lineSecretKey->setText(info.secret_key);
                ui->lineRemark->setText(info.remark);
                ui->saveSection->setChecked(true);
    });
}

void UiLoginDialog::onBtnLoginClicked()
{
    QJsonObject params;
    params["secretId"] = ui->lineSecretID->text().trimmed();
    params["secretKey"] = ui->lineSecretKey->text().trimmed();
    // 进入主界面
    MG->mGate->send(API::LOGIN::NORMAL, params);
}

void UiLoginDialog::onLoginSucceed()
{
    if (ui->saveSection->isChecked()) {
        // 保存登录信息
        MG->mDb->saveLoginInfo(ui->lineLoginName->text(), ui->lineSecretID->text(),
                               ui->lineSecretKey->text(), ui->lineRemark->text());
        updateLoginInfo(); // 更新登录账户
    } else {
        // 删除登录信息
        MG->mDb->removeLoginInfo(ui->lineSecretID->text());
    }
    accept(); // 发送accept信号，将会隐藏该窗口
}

void UiLoginDialog::onLoginError(int api, const QString &msg, const QJsonValue &req)
{
    Q_UNUSED(req) // 暂时没用上
    if (api != API::LOGIN::NORMAL)
        return;
    UiMessageBox().showMessage(STR("警告"), STR("登录失败: %1").arg(msg));
}

void UiLoginDialog::dealDBError(const QString &e)
{
     UiMessageBox().showMessage(STR("数据错误"), e);
}
