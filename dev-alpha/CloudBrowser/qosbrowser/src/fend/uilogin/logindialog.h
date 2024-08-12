#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include<QMessageBox>
#include<QMouseEvent>
#include<QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginDialog; }
QT_END_NAMESPACE

// 登录界面
class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    void complementLoginInfo();     // 补全数据

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
//    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_closeButton_clicked();

    void on_btnLogin_clicked();

    void onLoginSucceed();

    void onLoginError(int api, const QString &msg);

private:
    Ui::LoginDialog *ui;
    QPoint m_start;
};
#endif // LOGINDIALOG_H
