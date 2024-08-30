#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <QMap>
#include <QString>

typedef QMap<QString, QString> ErrorMap;
// 基本的异常类
class BaseException
{
public:
    BaseException(const QString& code, const QString& msg);

    static ErrorMap parseErrorCode(const QString& csvPath);
    static void generateErrorCodeHFile(const QString& csvPath, const QString &targetPath);

    QString msg() const;
    QString code() const;

private:
    QString m_code;
    QString m_msg;
};

#endif // EXCEPTIONS_H
