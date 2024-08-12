#ifndef VERSIONCMD_H
#define VERSIONCMD_H

#include "version.h"

#include <QStringList>

class VersionCmd : public Version
{
public:
    VersionCmd(int argc, char *argv[]);
    void setVersion();

    bool isVaild();
private:
    QStringList m_argv;
};

#endif // VERSIONCMD_H
