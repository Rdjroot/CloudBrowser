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
 * @brief Mysql执行SQL语句
 *
 */
class DbMySql
{
public:
    DbMySql();
    ~DbMySql();

    /**
     * @brief 连接数据库
     * @param dbname
     */
    void connect(const QString& dbname);

    /**
     * @brief 判断是否有数据存在，通常用于查询
     * @param sql
     * @return bool答案
     */
    bool exists(const QString &sql);

    /**
     * @brief 执行SQL
     * @param sql
     * @return 查询结果
     */
    QSqlQuery exec(const QString& sql);

    /**
     * @brief 执行SQL语句防注入
     * @param sql
     * @param variantList  参数列表
     * @return 查询结果
     */
    QSqlQuery exec(const QString& sql, QVariantList &variantList);

    /**
     * @brief 查询
     * @param sql
     * @return 查询结果（QList<RECORD>类型）
     */
    QList<RECORD> select(const QString& sql);

private:
    QSqlDatabase m_db;      // 数据库引擎
};

#endif // DBMYSQL_H
