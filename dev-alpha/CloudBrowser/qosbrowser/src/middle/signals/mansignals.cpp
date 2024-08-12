#include "mansignals.h"

Q_GLOBAL_STATIC(ManSignals, ins)
ManSignals::ManSignals(QObject *parent)
    : QObject{parent}
{}

ManSignals *ManSignals::instance()
{
    return ins();
}
