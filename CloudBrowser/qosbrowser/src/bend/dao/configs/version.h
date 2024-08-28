#ifndef VERSION_H
#define VERSION_H

#include<QJsonObject>
#include <QString>

// 获取版本，存储版本
class Version
{
public:
    Version();
    virtual void setVersion() = 0;

    QString version();
    QString versionNum();
    QString major() const;

protected:
    QString m_major;        // business 商用版 custom - 个人版
    QString m_env;          // dev alpha beta prod

    int m_v1;
    int m_v2;
    int m_v3;
};

#endif // VERSION_H
