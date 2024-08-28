#ifndef UILOGINDIALOG_H
#define UILOGINDIALOG_H

#include "src/fend/uicom/uiqosdialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class UiLoginDialog; }
QT_END_NAMESPACE

// 登录界面
class UiLoginDialog : public UiQosDialog
{
    Q_OBJECT

public:
    UiLoginDialog(QWidget *parent = nullptr);
    ~UiLoginDialog();

    void complementLoginInfo();     // 补全数据

protected:
   // bool eventFilter(QObject *watched, QEvent *event);  // 已采用继承，这里暂时不需要

private slots:
    void onBtnLoginClicked();
    void onLoginSucceed();
    void onLoginError(int api, const QString &msg, const QJsonValue &req);

private:
    Ui::UiLoginDialog *ui;
};
#endif // UILOGINDIALOG_H
