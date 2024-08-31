#ifndef MYBUCKET_H
#define MYBUCKET_H

#include <QObject>
#include<QString>

struct BaseObject
{
    bool isValid() const {return !isInvalid();}
    bool isInvalid() const {return name.isNull() || name.isEmpty();}
    QString name;
};
Q_DECLARE_METATYPE(BaseObject);     // 可以被QVairant使用

/**
 * @brief 自定义桶结构
 *
 * @var QString location
 * @var QString createDate
 * @var QString name
 */
struct MyBucket: public BaseObject
{
    MyBucket() = default;
    QString location;
    QString createDate;
};
Q_DECLARE_METATYPE(MyBucket);

/**
 * @brief 自定义对象结构
 *
 * @var QString name
 * @var QString lastmodified 最后一次操作方式
 * @var QString dir 目录 eg:books/
 * @var QString key 对象key，eg：books/aaa.txt
 * @var qulonglong size
 */
struct MyObject: public BaseObject
{
    bool isDir() const{return isValid() && name.endsWith("/");}
    bool isFile() const{return isValid() && !name.endsWith("/");}
    QString lastmodified;
    // qulonglong  == unsigned __int64 on Windows
    qulonglong size = 0;
    QString dir;
    QString key;
};
Q_DECLARE_METATYPE(MyObject);


#endif // MYBUCKET_H
