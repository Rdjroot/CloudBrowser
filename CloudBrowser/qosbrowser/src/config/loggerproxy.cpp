#include "loggerproxy.h"
#include "src/middle/manglobal.h"
#include "src/helper/filehelper.h"
#include <QJsonObject>
#include <QThread>

LoggerProxy::LoggerProxy(QObject *parent) : QObject(parent)
{
    // 默认日志级别为告警
    QJsonObject log_level = FileHelper::readAllJson(":/static/configs/default_config.json").toJsonObject();
    m_level = GLOBAL::LOG_LEVEL(log_level["log_level"].toInt());
}

LoggerProxy::~LoggerProxy()
{
    if(m_logger)
    {
        delete m_logger;
        m_logger = nullptr;
    }
}

const LoggerProxy &LoggerProxy::reset(const QString &file, int line, const QString &func)
{
    m_file = file;
    m_line = line;
    m_func = func;
    return *this;
}

void LoggerProxy::total(const QVariant &var, bool up) const
{
    doLog(GLOBAL::LOG_LEVEL::TOTAL, var, up);
}

void LoggerProxy::debug(const QVariant &var, bool up) const
{
    doLog(GLOBAL::LOG_LEVEL::DEBUG, var, up);
}

void LoggerProxy::info(const QVariant &var, bool up) const
{
    doLog(GLOBAL::LOG_LEVEL::INFO, var, up);
}

void LoggerProxy::warning(const QVariant &var, bool up) const
{
    doLog(GLOBAL::LOG_LEVEL::WARNING, var, up);
}

void LoggerProxy::error(const QVariant &var, bool up) const
{
    doLog(GLOBAL::LOG_LEVEL::ERROR_L, var, up);
}

void LoggerProxy::fatal(const QVariant &var, bool up) const
{
    doLog(GLOBAL::LOG_LEVEL::FATAL, var, up);
}

void LoggerProxy::setLevel(GLOBAL::LOG_LEVEL newLevel)
{
    m_level = newLevel;
    QString msg = QString("Change the Log Level, new Level is : %1")
                      .arg(GLOBAL::LOG_NAMES[newLevel]);
    mWarning(msg, true);
}


void LoggerProxy::setLogger(BasicLogger *newLogger)
{

    if(!m_logger)
    {
        m_logger = newLogger;
        connect(this, &LoggerProxy::sigLog, m_logger, &BasicLogger::onLog);
    }
}

void LoggerProxy::doLog(GLOBAL::LOG_LEVEL level, const QVariant &var, bool up) const
{
    if(!m_logger)       // 如果指针为空
    {
        return;
    }
    if(level >= m_level)
    {
        // 调用日志打印函数
        emit sigLog(m_file, m_line, m_func,QThread::currentThreadId(),level,var, up);
    }

}
