#ifndef UILOGINDIALOG_H
#define UILOGINDIALOG_H

#include "src/fend/uicom/uiqosdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class UiLoginDialog;
}
QT_END_NAMESPACE

/**
 * @brief 用户登录界面
 */
class UiLoginDialog : public UiQosDialog
{
    Q_OBJECT

public:
    UiLoginDialog(QWidget *parent = nullptr);
    ~UiLoginDialog();

    /**
     * @brief 根据登录名补全登录信息
     *
     */
    void updateLoginInfo();

private slots:
    /**
     * @brief 单击登录
     */
    void onBtnLoginClicked();

    /**
     * @brief 登录成功
     */
    void onLoginSucceed();

    /**
     * @brief 登录出错
     * @param api 调用的API
     * @param msg 报错信息
     * @param req 请求头
     */
    void onLoginError(int api, const QString &msg, const QJsonValue &req);

    /**
     * @brief 处理数据库错误
     * @param e 错误信息
     */
    void dealDBError(const QString &e);

private:
    Ui::UiLoginDialog *ui;
};
#endif // UILOGINDIALOG_H
