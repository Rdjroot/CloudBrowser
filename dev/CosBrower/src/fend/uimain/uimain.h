#ifndef UIMAIN_H
#define UIMAIN_H

#include <QWidget>
#include "src/fend/uilogin/logindialog.h"
#include <QDebug>

namespace Ui {
class UiMain;
}

class LoginDialog;

class UiMain : public QWidget
{
    Q_OBJECT

public:
    explicit UiMain(QWidget *parent = nullptr);
    ~UiMain();

    void showLoginDialog();
    void onUnLogin();
    void onUpload();

private:
    Ui::UiMain *ui;

    LoginDialog* m_loginDialog = nullptr;

private slots:
    void onButtonClicked(const QString& text);
};

#endif // UIMAIN_H
