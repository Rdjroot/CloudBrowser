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
    void init();

    /**
     * @brief 存储登录信息
     * @param name 名称
     * @param id
     * @param key   密码
     * @param remark 备注
     */
    void saveLoginInfo(const QString &name,const QString &id, const QString &key,const QString&remark);

    /**
     * @brief 删除登录信息（数据库和表中）
     * @param id
     */
    void removeLoginInfo(const QString &id);

    /**
     * @brief 返回登录账户在登录list中的索引
     * @param secretID
     * @return 索引(int)
     */
    int indexOfLoginInfo(const QString& secretID);

    /**
     * 返回所有登录名
     *
     */
    QStringList loginNameList();

    /**
     * @brief 根据name获取登录信息（id、密码等）
     * @param name 登录名
     * @return QStringList类型
     */
    LoginInfo loginInfoByName(const QString&name);


private:
    DaoLoginInfoMySql m_daoLoginInfomsq;    // mysql业务查询类
    QList<LoginInfo> m_loginInfoList;       // 暂存所有登录信息（当前设计未考虑用户过多，因为是本地程序）
};

#endif // MANDB_H
