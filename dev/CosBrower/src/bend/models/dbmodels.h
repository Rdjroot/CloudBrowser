#ifndef DBMODELS_H
#define DBMODELS_H

#include<QString>

struct LoginInfo
{
    QString name;
    QString secret_id;
    QString secret_key;
    QString remark;
    uint timestamp;
};


#endif // DBMODELS_H
