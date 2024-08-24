#include "bytehelper.h"

QString ByteHelper::toBeautifulStr(qulonglong bytes) {
    if (bytes < 1024)
        return QString("%1 B").arg(bytes);
    else if (bytes < 1024 * 1024)
        return QString("%1 KB").arg(bytes / 1024);
    else if (bytes < 1024 * 1024 * 1024)
        return QString("%1 MB").arg(bytes / (1024 * 1024));
    else
        return QString("%1 GB").arg(bytes / (1024 * 1024 * 1024));
}
