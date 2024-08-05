#include "daologininfo.h"

#include <QVariantList>

DaoLoginInfo::DaoLoginInfo()
{
}

bool DaoLoginInfo::exists(const QString &secretId)
{
    QString sql = QString(
                "select id from %1 where  "
                "secret_id = '%2';")
                .arg(CONF::DATA::TB_LOGIN_INFO, secretId);
    return m_db.exists(sql);
}

void DaoLoginInfo::insert(const LoginInfo &info)
{
    QString sql = QString(
                      "insert into %1 (name, secret_id, secret_key, remark, timestamp) "
                      "values (?, ?, ?, ?, ?)").arg(CONF::DATA::TB_LOGIN_INFO);
    QVariantList varList;
    varList << info.name
            << info.secret_id
            << info.secret_key
            << info.remark
            << info.timestamp;
    m_db.exec(sql, varList);
}

void DaoLoginInfo::update(const LoginInfo &info)
{
    QString sql = QString(
                      "update %1 "
                      "set name=?, "
                      "secret_key=?, "
                      "remark=?, "
                      "timestamp=? "
                      "where secret_id = ?")
                      .arg(CONF::DATA::TB_LOGIN_INFO);
    QVariantList varList;
    varList << info.name
            << info.secret_key
            << info.remark
            << info.timestamp
            << info.secret_id;
    m_db.exec(sql, varList);
}

void DaoLoginInfo::remove(const QString &secretId)
{
    QString sql = QString(
                      "delete from %1 where  "
                      "secret_id = ?;")
                      .arg(CONF::DATA::TB_LOGIN_INFO);
    QVariantList varList;
    varList << secretId;
    m_db.exec(sql, varList);
}

QList<LoginInfo> DaoLoginInfo::select()
{
    QString sql = QString(
                      "select name, secret_id, secret_key, remark from %1 "
                      "order by timestamp desc;")
                      .arg(CONF::DATA::TB_LOGIN_INFO);

    QList<LoginInfo> retList;
    QList<RECORD> recordList = m_db.select(sql);
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


void DaoLoginInfo::connect()
{
    m_db.connect(CONF::DATA::DATABASE);
}

void DaoLoginInfo::createTable()
{
    QString sql = FileHelper::readAllTxt(CONF::SQL::LOGIN_INFO_CREATE);
    m_db.exec(sql);
}
