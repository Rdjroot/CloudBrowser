#ifndef MANSIGNALS_H
#define MANSIGNALS_H

#include "src/middle/models/cloudmodels.h"
#include <QObject>

// #define MS ManSignals::instance()

/**
 * @brief 信号中心
 */
class ManSignals : public QObject
{
    Q_OBJECT
public:
    explicit ManSignals(QObject *parent = nullptr);
    static ManSignals* instance();

signals:
    void loginSuccess();
    void error(int api, const QString& msg);
    void bucketsSuccess(QList<MyBucket>);       // 返回用户对应存储桶
    void unLogin();
};

#endif // MANSIGNALS_H
