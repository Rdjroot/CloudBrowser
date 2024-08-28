#ifndef MANGLOBAL_H
#define MANGLOBAL_H

#include <QObject>

// 写入日志宏
#define MG ManGlobal::instance()
#define mLogIns MG->mLog
#define mTotal mLogIns->reset(QT_MESSAGELOG_FILE,QT_MESSAGELOG_LINE,QT_MESSAGELOG_FUNC).total
#define mDebug mLogIns->reset(QT_MESSAGELOG_FILE,QT_MESSAGELOG_LINE,QT_MESSAGELOG_FUNC).debug
#define mInfo mLogIns->reset(QT_MESSAGELOG_FILE,QT_MESSAGELOG_LINE,QT_MESSAGELOG_FUNC).info
#define mWarning mLogIns->reset(QT_MESSAGELOG_FILE,QT_MESSAGELOG_LINE,QT_MESSAGELOG_FUNC).warning
#define mError mLogIns->reset(QT_MESSAGELOG_FILE,QT_MESSAGELOG_LINE,QT_MESSAGELOG_FUNC).error
#define mFatal mLogIns->reset(QT_MESSAGELOG_FILE,QT_MESSAGELOG_LINE,QT_MESSAGELOG_FUNC).fatal

// 前置声明
class LoggerProxy;
class ManCloud;
class ManDB;
class ManPlugin;
class GateWay;
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
