#pragma warning
#include "mandb.h"
#include "src/config/global.h"

Q_GLOBAL_STATIC(ManDB, ins)

ManDB::ManDB(QObject *parent) : QObject(parent)
{
}

ManDB *ManDB::instance()
{
    return ins();
}

/**
 * 初始化
 * @brief ManDB::init
 * 连接数据库->创建表（*）->查询表中所有数据
 */
void ManDB::init()
{
    m_daoLoginInfomsq.connect();
    m_daoLoginInfomsq.createTable();
    m_loginInfoList = m_daoLoginInfomsq.select();
    qDebug()<< "初始化成功" ;
}

// 存储登录信息
void ManDB::saveLoginInfo(const QString &name, const QString &id, const QString &key, const QString &remark)
{
    LoginInfo info;
    info.name = (name == "" ? id: name);    // 如果为空直接获取id
    info.secret_id = id.trimmed();
    info.secret_key = key.trimmed();
    info.remark = remark.trimmed();
    info.timestamp = QDateTime::currentDateTimeUtc().toTime_t();        // 时间戳

    // qDebug() << QString("是否存在: %1").arg(info.secret_id);
    // qDebug() << m_daoLoginInfomsq.exists(info.secret_id);

    // 存在则更新，不存在则插入
    if(m_daoLoginInfomsq.exists(info.secret_id))
    {
        m_daoLoginInfomsq.update(info);
        m_loginInfoList[indexOfLoginInfo(info.secret_id)] = info;
    }
    else
    {
        m_daoLoginInfomsq.insert(info);
        m_loginInfoList.append(info);
    }
}

// 删除数据（数据库和表中）
void ManDB::removeLoginInfo(const QString &id)
{
    if(m_daoLoginInfomsq.exists(id))
    {
        m_daoLoginInfomsq.remove(id);
        m_loginInfoList.removeAt(indexOfLoginInfo(id));
    }
}

// 返回登录账户在登录list中的序列
int ManDB::indexOfLoginInfo(const QString &secretID)
{
    for(int i = 0; i < m_loginInfoList.size(); ++i)
    {
        if(m_loginInfoList[i].secret_id == secretID)
        {
            return i;
        }
    }
    throw  QString("获取登录信息索引失败 %1").arg(secretID);
}

/**
 * 返回所有的登录名
 *
*/
QStringList ManDB::loginNameList()
{
    QStringList words;
    for(int i = 0; i < m_loginInfoList.size(); ++i)
    {
        words.append(m_loginInfoList[i].name);
    }
    return words;
}

// 根据登录名查找登录信息
LoginInfo ManDB::loginInfoByName(const QString &name)
{
    for(int i = 0; i < m_loginInfoList.size(); ++i)
    {
        if(m_loginInfoList[i].name == name)
        {
            return m_loginInfoList[i];
        }
    }
    throw QString("通过名称查找登录信息失败 %1").arg(name);
}
