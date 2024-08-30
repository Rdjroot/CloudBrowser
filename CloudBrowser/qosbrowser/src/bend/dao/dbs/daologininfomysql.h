#ifndef DAOLOGININFOMYSQL_H
#define DAOLOGININFOMYSQL_H

#include "daologininfo.h"
#include "src/helper/dbmysql.h"
#include "src/middle/models/dbmodels.h"

/**
 * @brief 使用mysql操控业务数据表
 *
 * 含增删改查
 */
class DaoLoginInfoMySql : public DaoLoginInfo
{
public:
    DaoLoginInfoMySql();

    /**
     * @brief 账号是否存在
     * @param secretId  ID
     * @return bool 返回值
     */
    bool exists(const QString& secretId) override;

    /**
     * @brief 插入数据（用户）
     * @param info
     */
    void insert(const LoginInfo& info) override;

    /**
     * @brief 更新数据（用户）
     * @param info
     */
    void update(const LoginInfo& info) override;

    /**
     * @brief 删除数据（用户）
     * @param secretId
     */
    void remove(const QString& secretId) override;

    /**
     * @brief 查询表中所有数据
     * @return 数据列表
     */
    QList<LoginInfo> select() override;

    /**
     * @brief 连接数据库
     */
    void connect() override;

    /**
     * @brief 创建用户表
     */
    void createTable() override;

private:
    DbMySql m_db;
};

#endif // DAOLOGININFOMYSQL_H
