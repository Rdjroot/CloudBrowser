#ifndef UIMAIN_H
#define UIMAIN_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class UiMain;
}

class LoginDialog;

// 主界面
class UiMain : public QWidget
{
    Q_OBJECT

public:
    explicit UiMain(QWidget *parent = nullptr);
    ~UiMain();

    void onUnLogin();
    void onUpload();

private:
    Ui::UiMain *ui;

private slots:
    void onButtonClicked(const QString& text);
};

#endif // UIMAIN_H
