#ifndef BYTEHELPER_H
#define BYTEHELPER_H

#include <QString>

/**
 * @brief 处理字节数据
 */
class ByteHelper
{
public:
    ByteHelper() = default;

    /**
     * @brief 将字节流的数据变得易读
     * @param bytes qulonglong类型
     * @return 格式化的字节数据（eg: 1 B 1 KB 1 MB 1 GB）
     */
    static QString toBeautifulStr(qulonglong bytes);
};

#endif // BYTEHELPER_H
