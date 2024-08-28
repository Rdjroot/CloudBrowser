#include "mansignals.h"

ManSignals::ManSignals(QObject *parent)
    : QObject{parent}
{
    // 进行注册
    // 使一些三方、特殊的类型可以通过信号传递
    qRegisterMetaType<QList<MyBucket> >("QList<MyBucket>");
    qRegisterMetaType<QList<MyObject> >("QList<MyObject>");

}
