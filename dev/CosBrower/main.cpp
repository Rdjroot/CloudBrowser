#include "src/fend/uimain/uimain.h"
#include"src/helper/filehelper.h"
#include"src/bend/man/manbuckets.h"
#include"src/bend/man/mandb.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 读取文件中的qss
    QString qssStr = FileHelper::readAllTxt(":/static/qss/default.qss");
    // QApplication 读取文件中的qss
    a.setStyleSheet(qssStr);
    try {
        MDB->init();
    } catch (const QString &error) {
        qDebug() << "Error initializing ManDB:" << error;
        // Handle the error appropriately
    }

    UiMain w;
    w.showLoginDialog();
//    w.show();

    MB->setBuckets();
    return a.exec();

}
