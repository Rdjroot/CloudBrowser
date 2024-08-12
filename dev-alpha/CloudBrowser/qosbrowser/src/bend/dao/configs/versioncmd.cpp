#include "versioncmd.h"

VersionCmd::VersionCmd(int argc, char *argv[])
{
    // 判断是否正确
    // 格式应该为：custom.prod.1.2.3
    // 因为第一个参数都为可执行文件本身，所以实际要自定义的参数只有一个
    if(argc == 2)
    {
        QString args = argv[1];
        m_argv = args.split(".");
    }
}

void VersionCmd::setVersion()
{
    if(!isVaild())
    {
        throw  QString::fromUtf8("命令行格式错误 %1").arg(m_argv.join("."));
    }

    m_major = m_argv[0];        // 这里应该还要进行校验，
    m_env = m_argv[1];
    m_v1 = m_argv[2].toInt();
    m_v2 = m_argv[3].toInt();
    m_v3 = m_argv[4].toInt();
}

// 判断版本号格式是否正确
bool VersionCmd::isVaild()
{
    return m_argv.size() == 5;
}
