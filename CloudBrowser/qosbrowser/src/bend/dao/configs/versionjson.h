#ifndef VERSIONJSON_H
#define VERSIONJSON_H

#include "version.h"

#include <QDebug>

/**
 * 从配置文件中读取版本号
 *
 */
class VersionJson : public Version
{
public:
    /**
     * @brief 从配置文件中获取版本
     */
    VersionJson(const QString& path);

    /**
     * @brief 设置版本号
     */
    void setVersion();

private:
    QString m_path;
};

#endif // VERSIONJSON_H
