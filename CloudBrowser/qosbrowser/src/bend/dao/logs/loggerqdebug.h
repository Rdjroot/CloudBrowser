#ifndef LOGGERQDEBUG_H
#define LOGGERQDEBUG_H

#include "basiclogger.h"

#include <QThread>

class LoggerQDebug : public BasicLogger
{
    Q_OBJECT
public:
    explicit LoggerQDebug(QObject *parent = nullptr);
    ~LoggerQDebug();

protected:
    /**
     * @brief 打印日志
     * @param file  错误文件
     * @param line  行号
     * @param func  函数
     * @param tid   线程号
     * @param level 日志级别
     * @param var 日志内容
     * @param up  是否上传
     */
    virtual void  print(const QString &file, int line, const QString &func, void *tid,
                       int level, const QVariant& var, bool up) override;
private:
    /**
     * @brief 拦截器，会将qDebug的内容输出到日志文件中
     * @param type 枚举类型，定义不同的消息类型。
     * @param contex 日志的上下文信息，如文件名、行号等
     * @param msg 实际的日志消息文本
     */
    static void handle(QtMsgType type, const QMessageLogContext &contex, const QString &msg);
    QThread *m_td = nullptr;
};

#endif // LOGGERQDEBUG_H
