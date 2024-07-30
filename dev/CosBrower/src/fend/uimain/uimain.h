#ifndef UIMAIN_H
#define UIMAIN_H

#include <QWidget>
#include "src/fend/uilogin/logindialog.h"

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

private:
    Ui::UiMain *ui;

    LoginDialog* m_loginDialog = nullptr;
};

#endif // UIMAIN_H
