#ifndef FILEHELPER_H
#define FILEHELPER_H

#include<QString>
#include<QFile>
#include<QVariant>
#include<QJsonDocument>

/**
 * @brief 文件操作辅助类
 *
 * 用于读写文件，拼接路径
 *
 */
class FileHelper
{
public:
    FileHelper();

    /**
     * @brief 读取所有文件内容进行返回
     * @param filepath 路径
     * @return QString
     */
    static QString readAllTxt(const QString& filepath);

    /**
     * @brief 读取Json文件
     * @param filepath 文件路径
     * @return QVariant类文件内容
     */
    static QVariant readAllJson(const QString& filepath);

    /**
     * @brief 读取CSV文件，注意源文件的换行符和编码要正确
     * @param filepath 文件路径
     * @return 以QList<QStringList>类型返回
     */
    static QList<QStringList> readAllCsv(const QString& filepath);

    /**
     * @brief 拼接路径
     * @param path1
     * @param path2
     * @return  QString路径
     */
    static QString joinPath(const QString& path1, const QString& path2);    // 拼接路径

    /**
     * @brief 创建文件夹
     * @param path 路径
     * @return bool结果
     */
    static bool mkPath(const QString& path);

    /**
     * @brief 写入文件
     * @param lines 内容
     * @param filePath 路径
     */
    static void writeFile(const QStringList lines, const QString &filePath);
};

#endif // FILEHELPER_H
