#include "versionjson.h"
#include <QJsonObject>

VersionJson::VersionJson(const QString &path)
{
    m_path = path;
}

void VersionJson::setVersion()
{
    QJsonObject obj = FileHelper::readAllJson(m_path).toJsonObject();
    obj = obj["version"].toObject();
    m_major = obj["major"].toString();
    m_env = obj["env"].toString();
    m_v1 = obj["v1"].toInt();
    m_v2 = obj["v2"].toInt();
    m_v3 = obj["v3"].toInt();
    qDebug()<<obj<<m_v1;        // 打印版本号
}
