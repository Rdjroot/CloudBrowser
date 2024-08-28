#include "version.h"

Version::Version()
{

}

QString Version::version()
{
    return QString("%1.%2.%3").arg(m_major, m_env, versionNum());
}

QString Version::versionNum()
{
    return QString("%1.%2.%3").arg(m_v1, m_v2, m_v3);
}

QString Version::major() const
{
    return m_major;
}
