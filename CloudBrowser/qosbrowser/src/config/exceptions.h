#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <QMap>
#include <QString>

typedef QMap<QString, QString> ErrorMap;

/**
 * @brief 基本异常类
 *
 */
class BaseException
{
public:
    BaseException(const QString& code, const QString& msg);

    /**
     * @brief 解析错误码CSV文件
     * @param csvPath 文件路径
     * @return 返回map（QMap<QString, QString>）
     */
    static ErrorMap parseErrorCode(const QString& csvPath);

    /**
     * @brief 生成错误码头文件
     *
     * 代码中没有实时使用，需要的时候再调用
     *
     * @param csvPath 配置文件路径
     * @param targetPath 目标文件路径
     */
    static void generateErrorCodeHFile(const QString& csvPath, const QString &targetPath);

    /**
     * @brief 拼接错误信息
     * @return 返回报错内容
     */
    QString msg() const;

    /**
     * @brief 返回错误码
     * @return QString类型的错误码
     */
    QString code() const;

private:
    QString m_code;
    QString m_msg;
};

#endif // EXCEPTIONS_H
