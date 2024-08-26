﻿#ifndef FILEHELPER_H
#define FILEHELPER_H

#include<QString>
#include<QFile>
#include<QVariant>
#include<QJsonDocument>

// 文件操作辅助类
class FileHelper
{
public:
    FileHelper();

    static QString readAllTxt(const QString& filepath);  // 读取文本
    static QVariant readAllJson(const QString& filepath);   // 读取Json文件
    static QList<QStringList> readAllCsv(const QString& filepath);

    static QString joinPath(const QString& path1, const QString& path2);    // 拼接路径

    static bool mkPath(const QString& path);

    static void writeFile(const QStringList lines, const QString &filePath);
};

#endif // FILEHELPER_H