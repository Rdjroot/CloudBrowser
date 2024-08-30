#ifndef BASICLOGGER_H
#define BASICLOGGER_H

#include<QDate>
#include<QDebug>
#include<QObject>
#include<QString>
#include<QVariant>
#include<QThread>

/**
 * @brief 基础日志类，派生出该类来实现具体的日志记录
 */
class BasicLogger:public QObject
{
    Q_OBJECT
public:
    explicit BasicLogger(QObject *parent = nullptr);
    ~BasicLogger();

public slots:
    /**
     * @brief 处理日志信息的槽函数
     * @param file  错误文件
     * @param line  行号
     * @param func  函数
     * @param tid   线程号
     * @param level 日志级别
     * @param var 日志内容
     * @param up  是否上传
     */
    void onLog(const QString &file, int line, const QString &func, void *tid, int level,
               const QVariant& var, bool up);

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
    virtual void print(const QString &file, int line, const QString &func, void *tid,
                       int level, const QVariant& var, bool up) = 0;

    /**
     * @brief 日志路径
     * @return 当前写入日志路径
     */
    static QString filePath();

private:
    QThread* m_td =nullptr;
};

#endif // BASICLOGGER_H
