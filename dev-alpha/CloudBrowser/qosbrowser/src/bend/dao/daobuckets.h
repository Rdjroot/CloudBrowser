#ifndef DAOBUCKETS_H
#define DAOBUCKETS_H

#include<QList>
#include "src/middle/models/cloudmodels.h"
#include "src/helper/filehelper.h"
#include<QVariant>
#include <QJsonArray>
#include<QDebug>

// 应该会废弃
class DaoBuckets
{
public:
    DaoBuckets();
    // 从json文件中读取数据对象
    QList<MyBucket> bucketsFromMock(const QString &path);
};

#endif // DAOBUCKETS_H
