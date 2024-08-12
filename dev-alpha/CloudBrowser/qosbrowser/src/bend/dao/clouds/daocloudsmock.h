#ifndef DAOCLOUDSMOCK_H
#define DAOCLOUDSMOCK_H

#include "daoclouds.h"
#include <QJsonValue>
#include <QJsonArray>
#include <QDebug>
#include "src/helper/filehelper.h"

class DaoCloudsMock : public DaoClouds
{
public:
    DaoCloudsMock(const QString& path);
    virtual QList<MyBucket> buckets() override;

    QList<MyBucket> login(const QString secretId, const QString secretKey);
private:
    QJsonValue m_mock;
};

#endif // DAOCLOUDSMOCK_H
