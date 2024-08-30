#ifndef DAOLOGININFO_H
#define DAOLOGININFO_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include "src/config/globals.h"
#include <QSqlQuery>
#include "src/helper/dbmysql.h"
#include "src/middle/models/dbmodels.h"

/**
 * 抽象接口，用于适配不同数据库
 *
 * eg: sqlite mysql oracle
 *
 */
class DaoLoginInfo
{
public:
    DaoLoginInfo(){};

    virtual bool exists(const QString& secretId) = 0;
    virtual void insert(const LoginInfo& info) = 0;
    virtual void update(const LoginInfo& info) = 0;
    virtual void remove(const QString& secretId) = 0;
    virtual QList<LoginInfo> select() = 0;

    virtual void connect() = 0;
    virtual void createTable() = 0;
};

#endif // DAOLOGININFO_H
