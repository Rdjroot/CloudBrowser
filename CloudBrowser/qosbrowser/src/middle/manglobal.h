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

class ManGlobal : public QObject
{
    Q_OBJECT
public:
    explicit ManGlobal(QObject *parent = nullptr);
    ~ManGlobal();
    static ManGlobal* instance();

    void init(int argc, char *argv[]);

signals:

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
