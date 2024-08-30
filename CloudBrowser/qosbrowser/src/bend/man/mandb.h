#ifndef MANDB_H
#define MANDB_H

#include <QObject>
#include "src/bend/dao/dbs/daologininfomysql.h"
#include<QString>
#include<QDateTime>
#include<QList>

/**
 * @brief 业务层数据操作
 *
 * 调用Dao层接口进行业务层面的数据操作，不感知底层数据库及引擎
 *
 */
class ManDB : public QObject
{
    Q_OBJECT
public:
    explicit ManDB(QObject *parent = nullptr);
    ~ManDB();
    /**
     * @brief 初始化
     *
     * 连接数据库->创建表（*）->查询表中所有数据
     *
     */
    void init();        // 初始化数据库

    void saveLoginInfo(const QString &name,const QString &id, const QString &key,const QString&remark);
    void removeLoginInfo(const QString &id);
    int indexOfLoginInfo(const QString& secretID);

    /**
     * 返回所有的登录名
     *
     */
    QStringList loginNameList();

    /**
     * @brief 根据name获取登录信息（id、密码等）
     * @param name 登录名
     * @return QStringList类型
     */
    LoginInfo loginInfoByName(const QString&name);
signals:

private:
    DaoLoginInfoMySql m_daoLoginInfomsq;
    QList<LoginInfo> m_loginInfoList;
};

#endif // MANDB_H
