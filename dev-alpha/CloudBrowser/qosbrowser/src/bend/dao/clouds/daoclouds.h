#ifndef DAOCLOUDS_H
#define DAOCLOUDS_H

#include "src/middle/models/cloudmodels.h"
#include <QString>
#include<QList>

class DaoClouds
{
public:
    DaoClouds(){};
    virtual QList<MyBucket> buckets() = 0;
    virtual QList<MyBucket> login(const QString secretId, const QString secretKey) = 0;
private:
};
#endif // DAOCLOUDS_H
