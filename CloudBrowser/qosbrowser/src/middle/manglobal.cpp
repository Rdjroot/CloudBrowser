#include "manglobal.h"
#include "manmodels.h"
#include "src/bend/gateway.h"
#include "src/bend/man/mancloud.h"
#include "src/bend/man/mandb.h"
#include "src/plugins/manplugin.h"
#include "src/config/loggerproxy.h"
#include "src/middle/signals/mansignals.h"
#include <QApplication>

Q_GLOBAL_STATIC(ManGlobal, ins)

ManGlobal::ManGlobal(QObject *parent)
    : QObject{parent}
{
    mLog = new LoggerProxy(this);
    qDebug()<<"111";
    mCloud = new ManCloud(this);
    qDebug()<<"222";

    mSignal = new ManSignals(this);
    qDebug()<<"444";
    mPlugin = new ManPlugin(this);
    qDebug()<<"555";
    mGate = new GateWay(this);
    qDebug()<<"666";
    mDb = new ManDB();
    qDebug()<<"333";
    // mModels = new ManModels(this);
}

ManGlobal::~ManGlobal()
{

}

ManGlobal *ManGlobal::instance()
{
    return ins();
}

void ManGlobal::init(int argc, char *argv[])
{
    qDebug() << "1";
    mModels = new ManModels(this);
    qDebug() << 2;
    // 创建临时目录和日志目录 C:/Users/xxxx/AppData/Local/Temp/qos/logs
    FileHelper::mkPath(GLOBAL::PATH::LOG_DIR);
    FileHelper::mkPath(GLOBAL::PATH::TMP);
qDebug() << 3;
    mPlugin->installPlugins(argc, argv);         // 安装插件
qDebug() << 7;
    // QApplication读取文件中的qss
    QString qssStr = FileHelper::readAllTxt(":/static/qss/default.qss");

    qApp->setStyleSheet(qssStr);
    mDb->init();
    qDebug() << 8;
}
