#ifndef DBMODELS_H
#define DBMODELS_H

#include<QString>

/**
 * @brief 登录信息表
 *
 * @var QString name 名称
 * @var QString secret_id
 * @var QString secret_key 密码
 * @var QString remark 备注
 * @var uint timestamp 时间戳
 *
 */
struct LoginInfo
{
    QString name;
    QString secret_id;
    QString secret_key;
    QString remark;
    uint timestamp;
};


#endif // DBMODELS_H
