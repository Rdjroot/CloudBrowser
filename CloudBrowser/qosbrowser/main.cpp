#include "src/fend/uimain/uimain.h"
#include <QApplication>
#include <QTextCodec>
#include "src/middle/manglobal.h"
#include "src/fend/uilogin/uilogindialog.h"

// TODO 1 根据参考代码，完善所有代码，去除冗余代码
// TODO 2 通读代码 添加合理注释
// TODO 3 更改logo，调整按钮UI贴图 大小和风格统一吗，还有程序要有图标
// TODO 4 去除冗余日志，添加重要日志
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 设置编码
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    qDebug() <<"main函数";
    // 安装插件
    MG->init(argc, argv);

    UiMain w;
    UiLoginDialog login;
    login.show();
    return a.exec();
}
