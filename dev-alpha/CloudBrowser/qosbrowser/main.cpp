#include "src/fend/uimain/uimain.h"
#include <QApplication>
#include <QString>
#include <QTextCodec>
#include"src/middle/manglobal.h"
#include "src/fend/uilogin/logindialog.h"
#include "src/config/loggerproxy.h"

// qDebug() << QSqlDatabase::drivers();

// std::cout<<"1测试内容"<<std::endl;
// qDebug() << QString("2测试内容").trimmed();
// qDebug() << QString::fromLocal8Bit("3测试内容").trimmed();
// qDebug() << QString::fromUtf8("4测试内容").trimmed();
// qDebug() << QObject::tr("5测试内容").trimmed();
// qDebug() << QStringLiteral("6测试内容").trimmed();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 设置编码
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    MG->init(argc, argv);
    mInfo("这是主函数");
    UiMain w;
    LoginDialog login;
    login.show();
    return a.exec();
}
