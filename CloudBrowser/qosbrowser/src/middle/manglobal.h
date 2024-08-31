#ifndef MANGLOBAL_H
#define MANGLOBAL_H

#include <QOBJECT>
#include "src/bend/man/mandb.h"
// 写入日志宏
#define MG ManGlobal::instance()
#define mLogIns MG->mLog
#define mTotal mLogIns->reset(__FILE__, __LINE__, __FUNCTION__).total
#define mDebug mLogIns->reset(__FILE__, __LINE__, __FUNCTION__).debug
#define mInfo mLogIns->reset(__FILE__, __LINE__, __FUNCTION__).info
#define mWarning mLogIns->reset(__FILE__, __LINE__, __FUNCTION__).warning
#define mError mLogIns->reset(__FILE__, __LINE__, __FUNCTION__).error
#define mFatal mLogIns->reset(__FILE__, __LINE__, __FUNCTION__).fatal

// 前置声明
class LoggerProxy;
class ManCloud;
class ManPlugin;
class GateWay;
class ManDB;
class ManSignals;
class ManModels;

/**
 * @brief 管理全局单例类
 *
 * 含 数据库、网关、日志、数据模型、信号中心、插件、云对象
 *
 */
class ManGlobal : public QObject
{
    Q_OBJECT
public:
    explicit ManGlobal(QObject *parent = nullptr);
    ~ManGlobal();
    static ManGlobal* instance();

    /**
     * @brief 全局配置初始化
     * @param argc
     * @param argv
     */
    void init(int argc, char *argv[]);

public:
    LoggerProxy* mLog = nullptr;
    ManCloud *mCloud = nullptr;
    ManDB *mDb = nullptr;
    ManPlugin *mPlugin = nullptr;
    GateWay *mGate = nullptr;
    ManSignals *mSignal = nullptr;
    ManModels* mModels = nullptr;
};

#endif // MANGLOBAL_H
