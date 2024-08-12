#include "filehelper.h"

#include <QRegExp>
#include <QDir>

FileHelper::FileHelper()
{

}

// 读取所有文件内容进行返回
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

// 读取Json文件
QVariant FileHelper::readAllJson(const QString &filepath)
{
    QString data = FileHelper::readAllTxt(filepath);
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    return doc.toVariant();
}

// 拼接路径
QString FileHelper::joinPath(const QString &path1, const QString &path2)
{
    QString path = path1 + "/" + path2;
    QStringList pathList = path.split(QRegExp("[/\\\\]"),QString::SkipEmptyParts);
    path = pathList.join("/");     // 将list中的字符串通过‘/’拼接成一个
    return QDir::cleanPath(path);       //压缩路径
}

// 创建目录
bool FileHelper::mkPath(const QString &path)
{
    QDir dir;
    return dir.mkpath(path);
}
