#ifndef DAOLOGININFO_H
#define DAOLOGININFO_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include "src/config/config.h"
#include <QSqlQuery>
#include "src/helper/dbmysql.h"
#include "src/bend/models/dbmodels.h"

class DaoLoginInfo
{
public:
    DaoLoginInfo();

    bool exists(const QString& secretId);
    void insert(const LoginInfo& info);
    void update(const LoginInfo& info);
    void remove(const QString& secretId);
    QList<LoginInfo> select();

    void connect();
    void createTable();

private:
    DbMySql m_db;
};

#endif // DAOLOGININFO_H
