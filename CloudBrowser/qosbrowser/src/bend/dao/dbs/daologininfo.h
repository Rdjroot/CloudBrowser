#ifndef DAOLOGININFO_H
#define DAOLOGININFO_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include "src/config/global.h"
#include <QSqlQuery>
#include "src/helper/dbmysql.h"
#include "src/middle/models/dbmodels.h"

// 抽象接口，用于适用各种数据库
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

//private:
//    DbMySql m_db;
};

#endif // DAOLOGININFO_H
