#include "filehelper.h"

#include <QRegExp>
#include <QDir>

FileHelper::FileHelper()
{

}

QString FileHelper::readAllTxt(const QString &filepath)
{
    QFile file(filepath);
    if(file.exists() && file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();
        file.close();
        return data;
    }
    throw "READ FAILED";
}

QVariant FileHelper::readAllJson(const QString &filepath)
{
    QString data = FileHelper::readAllTxt(filepath);
    QJsonDocument doc = QJsonDocument::fromJson(data.toLocal8Bit());
    return doc.toVariant();
}

// 拼接路径
QString FileHelper::joinPath(const QString &path1, const QString &path2)
{
    QString path = path1 + "/" + path2;
    QStringList pathList = path.split(QRegExp("[/\\\\]"),QString::SkipEmptyParts);
    path = pathList.join("/");
    return QDir::cleanPath(path);
}

// 创建目录
bool FileHelper::mkPath(const QString &path)
{
    QDir dir;
    return dir.mkpath(path);
}
