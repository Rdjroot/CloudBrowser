#ifndef DAOLOGININFOMYSQL_H
#define DAOLOGININFOMYSQL_H

#include "daologininfo.h"
#include "src/helper/dbmysql.h"
#include "src/middle/models/dbmodels.h"

class DaoLoginInfoMySql : public DaoLoginInfo
{
public:
    DaoLoginInfoMySql();


    bool exists(const QString& secretId) override;
    void insert(const LoginInfo& info) override;
    void update(const LoginInfo& info) override;
    void remove(const QString& secretId) override;
    QList<LoginInfo> select() override;

    void connect() override;
    void createTable() override;

private:
    DbMySql m_db;
};

#endif // DAOLOGININFOMYSQL_H
