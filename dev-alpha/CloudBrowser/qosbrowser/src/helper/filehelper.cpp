#include "filehelper.h"
#include<iostream>
#include <QRegExp>
#include <QDir>
#include <QIODevice>

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

// 读取CSV文件，注意源文件的换行符和编码要正确
QList<QStringList> FileHelper::readAllCsv(const QString &filepath)
{
    QList<QStringList> records;
    QFile file(filepath);           // 打开文件
    if(file.exists() && file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        while(!stream.atEnd()){
            QString line = stream.readLine();
            QStringList row = line.split(',');      // 拆分行
            records.append(row);            // 一行数据存为一条
        }
        file.close();
    }
    return records;
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

// 写入文件
void FileHelper::writeFile(const QStringList lines, const QString &filePath)
{
    QFile file(filePath);
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream.setCodec("UTF-8");
        for(const auto&line: lines)
        {
            stream << line <<endl;
        }
        file.close();
        return;
    }
    throw "写入文件失败";
}
