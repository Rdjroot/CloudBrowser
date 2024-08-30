#ifndef LOGGERPROXY_H
#define LOGGERPROXY_H

#include <QObject>
#include <QString>
#include "src/bend/dao/logs/basiclogger.h"
#include "globals.h"

/**
 * @brief 日志代理
 *
 * 设置日志级别，在业务代码中调用日志输出接口
 *
 */
class LoggerProxy : public QObject
{
    Q_OBJECT
public:
    explicit LoggerProxy(QObject *parent = nullptr);
    ~LoggerProxy();

    /**
     * @brief 重设日志信息
     * @param file 文件
     * @param line 行号
     * @param func 函数
     * @return this指针
     */
    const LoggerProxy& reset(const QString& file, int line, const QString& func);

    /**
     * @brief total级日志
     * @param var 日志信息
     * @param up 是否上传
     */
    void total(const QVariant& var, bool up=false) const;

    /**
     * @brief debug级日志
     * @param var 日志信息
     * @param up 是否上传
     */
    void debug(const QVariant& var, bool up=false) const;

    /**
     * @brief info级日志
     * @param var 日志信息
     * @param up 是否上传
     */
    void info(const QVariant& var, bool up=false) const;

    /**
     * @brief warning级日志
     * @param var 日志信息
     * @param up 是否上传
     */
    void warning(const QVariant& var, bool up=false) const;

    /**
     * @brief error级日志
     * @param var 日志信息
     * @param up 是否上传
     */
    void error(const QVariant& var, bool up=true) const;

    /**
     * @brief fatal级日志
     * @param var 日志信息
     * @param up 是否上传
     */
    void fatal(const QVariant& var, bool up=true) const;

    /**
     * @brief 设置日志级别
     *
     * 大于该级别的日志，会输出
     *
     * @param newLevel 日志级别
     */
    void setLevel(GLOBAL::LOG_LEVEL newLevel);

    /**
     * @brief 设置日志具体派生类
     *
     * 在插件层调用
     *
     * @param newLogger log派生类
     */
    void setLogger(BasicLogger *newLogger);

signals:
    void sigLog(const QString& file, int line, const QString& func, void* tid,
                int level, const QVariant& var, bool up) const;

private:
    /**
     * @brief 调用日志输出接口
     * @param level 日志级别
     * @param var 日志内容
     * @param up 是否上传
     */
    void doLog(GLOBAL::LOG_LEVEL level, const QVariant& var, bool up) const;

private:
    BasicLogger* m_logger = nullptr;
    GLOBAL::LOG_LEVEL m_level;
    QString m_file;     //日志发生的文件
    int m_line;         // 日志发生的行数
    QString m_func;     // 日志发生的函数
};

#endif // LOGGERPROXY_H
