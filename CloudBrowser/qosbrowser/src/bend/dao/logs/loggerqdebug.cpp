#include "loggerqdebug.h"
#include"src/config/global.h"

#include <QIODevice>
#include <QString>
#include <QTextStream>
#include<iostream>

LoggerQDebug::LoggerQDebug(QObject *parent)
    : BasicLogger(parent)
{
    // 回调函数
    // 由qDebug、qWarnng、qCritical、qFatal函数进行触发，
    // qDebug、qWarnng、qCritical、qFatal函数处理的消息文本
    // 会被qInstallMsgHandler所指向的回调函数截获，允许用户自己来处理输出的消息文本。
    qInstallMessageHandler(handle);
}

LoggerQDebug::~LoggerQDebug()
{

}

// 这里的tid暂时没用上，后续可以考虑加上
void LoggerQDebug::print(const QString &file, int line, const QString &func, void *tid, int level, const QVariant &var, bool up)
{
    Q_UNUSED(up);
    Q_UNUSED(tid);
    Q_UNUSED(func);
    QDateTime dt;
    QString dtStr = dt.currentDateTime().toString(Qt::ISODate);         // 时间
    QString front = QString::fromLocal8Bit("%1[%2] %3:%4 -")            // 日志打印时包含时间、级别、文件、行号
                    .arg(dtStr,GLOBAL::LOG_NAMES[level],file)
                    .arg(line);
    front = front.replace("..\\","");
    // 使用qDebug而不是直接存文件，是为了打印QVariant类型 日志打印
    qDebug() << front.toLocal8Bit().data() << var;
}


// 拦截器，会将qDebug的内容输出到日志文件中
void LoggerQDebug::handle(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(type);
    Q_UNUSED(context);
    QFile file(filePath());
    QString key("QVariant(");
    QString message = msg;
    message.replace(msg.indexOf(key),key.size(),"").chop(1);        //chop(1)去掉右边的小日志

    if(file.open(QIODevice::WriteOnly|QIODevice::Append))
    {
        QTextStream stream(&file);      // 输入到文件流中
        stream << message <<endl;
        file.close();
    }

    // 用於控制台输出
    std::cout<<message.toUtf8().data() <<std::endl;
}
