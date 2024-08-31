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
    mCloud = new ManCloud(this);
    mSignal = new ManSignals(this);
    mPlugin = new ManPlugin(this);
    mGate = new GateWay(this);
    mDb = new ManDB(this);
}

ManGlobal::~ManGlobal()
{
    delete mLog;
    delete mCloud;
    delete mSignal;
    delete mPlugin;
    delete mGate;
    delete mDb;
}

ManGlobal *ManGlobal::instance()
{
    return ins();
}

void ManGlobal::init(int argc, char *argv[])
{

    mModels = new ManModels(this);

    // 创建临时目录和日志目录 C:/Users/xxxx/AppData/Local/Temp/qos/logs
    FileHelper::mkPath(GLOBAL::PATH::LOG_DIR);
    FileHelper::mkPath(GLOBAL::PATH::TMP);

    // 安装插件
    mPlugin->installPlugins(argc, argv);

    // QApplication读取文件中的qss
    QString qssStr = FileHelper::readAllTxt(":/static/qss/default.qss");

    // 配置前端美化内容
    qApp->setStyleSheet(qssStr);

    // 初始化数据库
    mDb->init();
}
