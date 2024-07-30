#ifndef FILEHELPER_H
#define FILEHELPER_H

#include<QString>
#include<QFile>

class FileHelper
{
public:
    FileHelper();

    static QString readAllTxt(const QString& filepath);
};

#endif // FILEHELPER_H
