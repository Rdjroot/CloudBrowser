#include "daologininfomysql.h"
#include "src/config/loggerproxy.h"
#include "src/middle/manglobal.h"
#include <QVariantList>


DaoLoginInfoMySql::DaoLoginInfoMySql()
{
}

bool DaoLoginInfoMySql::exists(const QString &secretId)
{
    // 查询secretId是否存在
    QString sql = QString(
                "select id from %1 where  "
                "secret_id = '%2';")
                .arg(GLOBAL::DATA::TB_LOGIN_INFO, secretId);
    return m_db.exists(sql);
}

void DaoLoginInfoMySql::insert(const LoginInfo &info)
{
    QString sql = QString(
                      "insert into %1 (name, secret_id, secret_key, remark, timestamp) "
                      "values (?, ?, ?, ?, ?)").arg(GLOBAL::DATA::TB_LOGIN_INFO);
    QVariantList varList;
    varList << info.name
            << info.secret_id
            << info.secret_key
            << info.remark
            << info.timestamp;
    m_db.exec(sql, varList);
}


void DaoLoginInfoMySql::update(const LoginInfo &info)
{
    QString sql = QString(
                      "update %1 "
                      "set name=?, "
                      "secret_key=?, "
                      "remark=?, "
                      "timestamp=? "
                      "where secret_id = ?")
                      .arg(GLOBAL::DATA::TB_LOGIN_INFO);
    QVariantList varList;
    varList << info.name
            << info.secret_key
            << info.remark
            << info.timestamp
            << info.secret_id;
    m_db.exec(sql, varList);
}

void DaoLoginInfoMySql::remove(const QString &secretId)
{
    QString sql = QString(
                      "delete from %1 where  "
                      "secret_id = ?;")
                      .arg(GLOBAL::DATA::TB_LOGIN_INFO);
    QVariantList varList;
    varList << secretId;
    m_db.exec(sql, varList);
}


QList<LoginInfo> DaoLoginInfoMySql::select()
{
    // 查询整张表，按时间戳倒序
    QString sql = QString(
                      "select name, secret_id, secret_key, remark from %1 "
                      "order by timestamp desc;")
                      .arg(GLOBAL::DATA::TB_LOGIN_INFO);

    QList<LoginInfo> retList;
    QList<RECORD> recordList = m_db.select(sql);

    // record是qmap<qstring,qvariant> 类型的元素
    for (const auto& record: recordList)
    {
        LoginInfo info;
        info.name = record["name"].toString();
        info.secret_id = record["secret_id"].toString();
        info.secret_key = record["secret_key"].toString();
        info.remark = record["remark"].toString();

        retList.append(info);
    }
   return retList;
}

void DaoLoginInfoMySql::connect()
{
    m_db.connect(GLOBAL::DATA::DATABASE);
}

void DaoLoginInfoMySql::createTable()
{
    // 执行创建表
    QString sql = FileHelper::readAllTxt(GLOBAL::SQL::LOGIN_INFO_CREATE);
    m_db.exec(sql);
}
