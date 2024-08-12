#include "src/fend/uimain/uimain.h"
#include"src/helper/filehelper.h"
#include"src/bend/man/mancloud.h"
#include"src/bend/man/mandb.h"
#include <QApplication>
#include <QString>
#include <QTextCodec>
#include"src/plugins/manplugin.h"
#include"src/config/loggerproxy.h"
#include <iostream>


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

    MP->installPlugins(argc, argv);         // 安装插件

    // 读取文件中的qss
    QString qssStr = FileHelper::readAllTxt(":/static/qss/default.qss");
    // QApplication 读取文件中的qss
    a.setStyleSheet(qssStr);

    MDB->init();

    UiMain w;
    LoginDialog login;

    login.show();

    // MC->setBuckets();       设置主界面的mock数据
    return a.exec();

}
