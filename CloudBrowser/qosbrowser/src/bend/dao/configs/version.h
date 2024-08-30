#ifndef VERSION_H
#define VERSION_H

#include<QJsonObject>
#include <QString>

/**
 * @brief 获取产品版本号
 *
 * 本项目没有正式启用该功能，没有区分不同类型版本。
 */
class Version
{
public:
    Version();
    virtual void setVersion() = 0;

    /**
     * @brief 获取版本
     * @return 版本名，如business dev 1.1.1
     */
    QString version();

    /**
     * @brief 版本号
     * @return 如 1.1.1
     */
    QString versionNum();

    /**
     * @brief 版本类型
     * @return custom
     */
    QString major() const;

protected:
    QString m_major;        // business 商用版 custom - 个人版
    QString m_env;          // dev alpha beta prod

    int m_v1;
    int m_v2;
    int m_v3;
};

#endif // VERSION_H
