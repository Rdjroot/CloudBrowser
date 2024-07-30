#include "filehelper.h"

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
