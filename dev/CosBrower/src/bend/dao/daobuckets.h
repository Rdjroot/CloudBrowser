#ifndef DAOBUCKETS_H
#define DAOBUCKETS_H

#include<QList>
#include "src/bend/models/mybucket.h"
#include "src/helper/filehelper.h"
#include<QVariant>
#include <QJsonArray>
#include<QDebug>

class DaoBuckets
{
public:
    DaoBuckets();
    // 从json文件中读取数据对象
    QList<MyBucket> bucketsFromMock(const QString &path);
};

#endif // DAOBUCKETS_H
