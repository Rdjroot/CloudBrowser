#ifndef DBMODELS_H
#define DBMODELS_H

#include<QString>

// 登录表
struct LoginInfo
{
    QString name;       // 名称
    QString secret_id;  // id
    QString secret_key; // 密码
    QString remark;     // 备注
    uint timestamp;     // 时间戳
};


#endif // DBMODELS_H
