#include "src/fend/uicom/uimessagebox.h"
#include "src/fend/uimain/uimain.h"
#include <QApplication>
#include <QString>
#include <QTextCodec>
#include"src/middle/manglobal.h"
#include "src/fend/uilogin/uilogindialog.h"
#include <src/fend/uicom/uipagewidget.h>
#include <src/fend/uimain/uibucketstablewidget.h>

// TODO 1、调整按钮UI贴图 大小和风格统一
// TODO 2、没有完善的log功能
// TODO 3、悬停显示
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 设置编码
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    MG->init(argc, argv);
    UiMain w;
    UiLoginDialog login;
    login.show();
    return a.exec();
}
