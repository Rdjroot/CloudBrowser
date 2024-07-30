#include "logindialog.h"

#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 点击完登录，弹出主窗口
    // 点击关闭，退出当前应用程序
    LoginDialog w;
//    w.show();
    int code = w.exec();        // 使用exec显示主窗口，窗口直接被设置成了模态窗口


    QWidget m;
    m.setWindowTitle("主窗口");
    if(code == QDialog::Accepted)
    {
        m.show();
        return a.exec();
    }
    return 0;

}
