#ifndef VERSIONJSON_H
#define VERSIONJSON_H

#include "version.h"
#include "src/helper/filehelper.h"
#include <QDebug>

// 从配置文件中读取版本号
class VersionJson : public Version
{
public:
    VersionJson(const QString& path);
    void setVersion();

private:
    QString m_path;
};

#endif // VERSIONJSON_H
