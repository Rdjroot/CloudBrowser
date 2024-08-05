#include "dbmysql.h"
#include "src/config/config.h"

#include <QSqlRecord>


DbMySql::DbMySql()
{
    m_db = QSqlDatabase::addDatabase("QMYSQL");
}

DbMySql::~DbMySql()
{
    if(m_db.isOpen())
    {
        m_db.close();
    }
}

void DbMySql::connect(const QString &dbpath)
{

    m_db.setHostName(CONF::NET::HOST);
    m_db.setUserName(CONF::USER::DEVNAME);
    m_db.setPassword(CONF::USER::PASSWORD);
    m_db.setDatabaseName(dbpath);           // 设置打开的数据库

    if(!m_db.open())
    {
        throw QString::fromLocal8Bit("打开数据库失败: %1 %2").arg(dbpath, m_db.lastError().text());
    }
}

bool DbMySql::exists(const QString &sql)
{
    QSqlQuery query = exec(sql);
    return query.next();        // 如果有数据，next == true
}

QSqlQuery DbMySql::exec(const QString &sql)
{
    QSqlQuery query;
    if(!query.exec(sql))
    {
        throw QString::fromLocal8Bit("执行sql失败：%1 %2").arg(sql,m_db.lastError().text());
    }
    return query;
}

QSqlQuery DbMySql::exec(const QString &sql, QVariantList &variantList)
{
    QSqlQuery query;

    if(!query.prepare(sql))
    {
        throw QString::fromLocal8Bit("预编译sql失败：%1 %2").arg(sql,m_db.lastError().text());
    }

    for(int i = 0; i < variantList.size(); i++)
    {
        query.bindValue(i, variantList[i]);
    }

    if(!query.exec())
    {
        throw QString::fromLocal8Bit("执行sql bindvalue失败：%1 %2").arg(sql,m_db.lastError().text());
    }

    return query;
}

// 根据sql查询
QList<RECORD> DbMySql::select(const QString& sql)
{
    QList<RECORD> retList;
    QSqlQuery query = exec(sql);

    while(query.next())             // 遍历结果集
    {
        RECORD ret;

        QSqlRecord record = query.record();     // 数据库中的一行记录
        for(int i = 0; i < record.count(); ++i)
        {
            QString name = record.fieldName(i);
            QVariant value = record.value(i);
            ret[name] = value;
        }
        qDebug() << "查询出结果" <<ret;
        retList.append(ret);
    }
    return retList;
}
