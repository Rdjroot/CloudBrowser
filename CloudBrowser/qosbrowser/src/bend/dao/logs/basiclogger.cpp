#include "basiclogger.h"

#include <src/helper/filehelper.h>
#include<src/config/global.h>

/**
  * 基础日志类，派生出该类来实现具体的日志记录
 * @brief BasicLogger::BasicLogger
 * @param parent
 * 使日志的记录在单独的线程中执行
 */
BasicLogger::BasicLogger(QObject *parent)
    :QObject(parent)
{
    m_td = new QThread();
    moveToThread(m_td);
    m_td->start();
}

BasicLogger::~BasicLogger()
{
    // 等待线程运行结束后停止
    if(m_td->isRunning())
    {
        m_td->quit();       // 让线程退出事件循环
        if(m_td->wait(1000))        // 等待1000毫秒
        {
            m_td->terminate();      // 强行关闭
            m_td->wait(1000);
        }
    }
    delete m_td;
}

void BasicLogger::onLog(const QString &file, int line, const QString &func, void *tid, int level, const QVariant &var, bool up)
{
    print(file, line, func,tid,level,var,up);   // 调用派生类打印
}

// 返回日志文件的路径
QString BasicLogger::filePath()
{
    // 获取当前时间
    QString name = QDate::currentDate().toString(Qt::ISODate);

    // 拼接路径
    return FileHelper::joinPath(GLOBAL::PATH::LOG_DIR, QString::fromLocal8Bit("%1.log").arg(name));
}
