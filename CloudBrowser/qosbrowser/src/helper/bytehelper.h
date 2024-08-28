#ifndef BYTEHELPER_H
#define BYTEHELPER_H

#include <QString>


class ByteHelper
{
public:
    ByteHelper() = default;
    static QString toBeautifulStr(qulonglong bytes);
};

#endif // BYTEHELPER_H
