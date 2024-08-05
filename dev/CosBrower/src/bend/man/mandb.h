#ifndef MANDB_H
#define MANDB_H

#include <QObject>
#include "src/bend/dao/daologininfo.h"
#include<QString>
#include<QDateTime>
#include<QList>

#define MDB ManDB::instance()

class ManDB : public QObject
{
    Q_OBJECT
public:
    explicit ManDB(QObject *parent = nullptr);

    static ManDB* instance();

    void init();        // 初始化数据库

    void saveLoginInfo(const QString &name,const QString &id, const QString &key,const QString&remark);
    void removeLoginInfo(const QString &id);
    int indexOfLoginInfo(const QString& secretID);
    QStringList loginNameList();            // 返回一个关联的登录名
    LoginInfo loginInfoByName(const QString&name);
signals:

private:
    DaoLoginInfo m_daoLoginInfo;
    QList<LoginInfo> m_loginInfoList;
};

#endif // MANDB_H
