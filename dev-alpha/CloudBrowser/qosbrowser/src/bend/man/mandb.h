#ifndef MANDB_H
#define MANDB_H

#include <QObject>
#include "src/bend/dao/dbs/daologininfomysql.h"
#include<QString>
#include<QDateTime>
#include<QList>

#define MDB ManDB::instance()

// 业务层面的对数据库的操作
class ManDB : public QObject
{
    Q_OBJECT
public:
    explicit ManDB(QObject *parent = nullptr);

    static ManDB* instance();

    void init();        // 初始化数据库

    void saveLoginInfo(const QString &name,const QString &id, const QString &key,const QString&remark);
    void removeLoginInfo(const QString &id);
    int indexOfLoginInfo(const QString& secretID);
    QStringList loginNameList();            // 返回一个关联的登录名
    LoginInfo loginInfoByName(const QString&name);
signals:

private:
    DaoLoginInfoMySql m_daoLoginInfomsq;
    QList<LoginInfo> m_loginInfoList;
};

#endif // MANDB_H
