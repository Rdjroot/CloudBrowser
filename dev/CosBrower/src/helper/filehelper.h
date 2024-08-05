#ifndef FILEHELPER_H
#define FILEHELPER_H

#include<QString>
#include<QFile>
#include<QVariant>
#include<QJsonDocument>

class FileHelper
{
public:
    FileHelper();

    static QString readAllTxt(const QString& filepath);
    static QVariant readAllJson(const QString& filepath);

    static QString joinPath(const QString& path1, const QString& path2);    // 拼接路径

    static bool mkPath(const QString& path);
};

#endif // FILEHELPER_H
