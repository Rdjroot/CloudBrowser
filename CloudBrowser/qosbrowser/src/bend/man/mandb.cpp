#include "mandb.h"
#include "src/config/loggerproxy.h"
#include "src/middle/manglobal.h"

ManDB::ManDB(QObject *parent) : QObject(parent)
{
}

ManDB::~ManDB()
{
    qDebug() <<"ManDB destroyed.";

}

void ManDB::init()
{
    m_daoLoginInfomsq.connect();
    m_daoLoginInfomsq.createTable();
    m_loginInfoList = m_daoLoginInfomsq.select();
}

void ManDB::saveLoginInfo(const QString &name, const QString &id, const QString &key, const QString &remark)
{
    LoginInfo info;
    info.name = (name == "" ? id: name);    // 如果为空直接获取id
    info.secret_id = id.trimmed();
    info.secret_key = key.trimmed();
    info.remark = remark.trimmed();
    info.timestamp = QDateTime::currentDateTimeUtc().toTime_t();        // 时间戳

    // 存在则更新，不存在则插入
    // 这里需要捕获db操作可能出现的异常
    try{
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
    } catch(const QString& e){
        mError(e);
        emit errorOccurred(e);
    }
}

void ManDB::removeLoginInfo(const QString &id)
{
    try {
        if (m_daoLoginInfomsq.exists(id)) {
            m_daoLoginInfomsq.remove(id);
            m_loginInfoList.removeAt(indexOfLoginInfo(id));
        }
    } catch (const QString &e) {
        mError(e);
        emit errorOccurred(e);
    }
}

int ManDB::indexOfLoginInfo(const QString &secretID)
{
    // 遍历查询很慢，但考虑到本地一般不会有太多用户
    for(int i = 0; i < m_loginInfoList.size(); ++i)
    {
        if(m_loginInfoList[i].secret_id == secretID)
        {
            return i;
        }
    }
    throw  QString("获取登录信息索引失败 %1").arg(secretID);
}


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
