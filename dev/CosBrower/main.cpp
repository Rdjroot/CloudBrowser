#include "src/fend/uimain/uimain.h"
#include"src/helper/filehelper.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 读取文件中的qss
    QString qssStr = FileHelper::readAllTxt(":/img/qss/default.qss");
    // QApplication 读取文件中的qss
    a.setStyleSheet(qssStr);
    UiMain w;
    w.showLoginDialog();
    //    w.show();
    return a.exec();
}
