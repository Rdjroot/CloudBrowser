#ifndef VERSIONCMD_H
#define VERSIONCMD_H

#include "version.h"

#include <QStringList>

/**
 * @brief 使用命令行指定版本
 */
class VersionCmd : public Version
{
public:
    VersionCmd(int argc, char *argv[]);

    /**
     * @brief 设置版本号
     */
    void setVersion();

    /**
     * @brief 版本名称是否合理
     * @return bool结果
     */
    bool isVaild();
private:
    QStringList m_argv;
};

#endif // VERSIONCMD_H
