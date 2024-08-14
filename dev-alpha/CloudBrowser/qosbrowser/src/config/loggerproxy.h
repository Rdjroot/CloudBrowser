#ifndef LOGGERPROXY_H
#define LOGGERPROXY_H

#include <QObject>
#include <QString>
#include "src/bend/dao/logs/basiclogger.h"
#include "global.h"

using namespace GLOBAL;

// 日志代理类
class LoggerProxy : public QObject
{
    Q_OBJECT
public:
    explicit LoggerProxy(QObject *parent = nullptr);
    ~LoggerProxy();

    const LoggerProxy& reset(const QString& file, int line, const QString& func);

    static LoggerProxy* instance();

    void total(const QVariant& var, bool up=false) const;
    void debug(const QVariant& var, bool up=false) const;
    void info(const QVariant& var, bool up=false) const;
    void warning(const QVariant& var, bool up=false) const;
    void error(const QVariant& var, bool up=true) const;
    void fatal(const QVariant& var, bool up=true) const;
    void setLevel(GLOBAL::LOG_LEVEL newLevel);
    void setLogger(BasicLogger *newLogger);

signals:
    void sigLog(const QString& file, int line, const QString& func, void* tid,
                int level, const QVariant& var, bool up) const;

private:
    void doLog(GLOBAL::LOG_LEVEL level, const QVariant& var, bool up) const;

private:
    BasicLogger* m_logger = nullptr;
    GLOBAL::LOG_LEVEL m_level;
    QString m_file;     //日志发生的文件
    int m_line;         // 日志发生的行数
    QString m_func;     // 日志发生的函数？也可以是自定义文字
};

#endif // LOGGERPROXY_H
