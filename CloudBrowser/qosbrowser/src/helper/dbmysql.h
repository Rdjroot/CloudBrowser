#ifndef DBMYSQL_H
#define DBMYSQL_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QList>
#include <QVariant>
#include <QMap>
#include <QDebug>
#include <QVariantList>

typedef QMap<QString, QVariant> RECORD;

/**
 * @brief Mysql数据库执行操作
 */
class DbMySql
{
public:
    DbMySql();
    ~DbMySql();

    void connect(const QString& dbname);
    bool exists(const QString &sql);
    QSqlQuery exec(const QString& sql);      // 执行sql语句
    QSqlQuery exec(const QString& sql, QVariantList &variantList);// 执行sql语句
    QList<RECORD> select(const QString& sql);

private:
    QSqlDatabase m_db;
};

#endif // DBMYSQL_H
