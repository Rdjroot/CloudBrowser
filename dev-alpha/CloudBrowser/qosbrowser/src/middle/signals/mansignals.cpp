#include "mansignals.h"

Q_GLOBAL_STATIC(ManSignals, ins)
ManSignals::ManSignals(QObject *parent)
    : QObject{parent}
{
    // 进行注册
    // 使一些三方、特殊的类型可以通过信号传递
    qRegisterMetaType<QList<MyBucket> >("QList<MyBucket>");
}

ManSignals *ManSignals::instance()
{
    return ins();
}
