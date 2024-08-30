#include "exceptions.h"
#include "src/config/common.h"
#include<iostream>
#include "src/helper/filehelper.h"


BaseException::BaseException(const QString &code, const QString &msg)
{
    m_code = code;
    m_msg = msg;
}

// 解析csv文件
ErrorMap BaseException::parseErrorCode(const QString &csvPath)
{
    ErrorMap m_map;
    int sectionCount = 6;
    QList<QStringList> records = FileHelper::readAllCsv(csvPath);

    for(int i = 1; i < records.size(); i++)
    {
        auto record = records[i];

        QString code;
        QString msg;
        for(int j = 0; j < sectionCount; ++j)
        {
            if(record[j] =="")
            {
                code += "0";
            }
            else{
                QStringList strs = record[j].split("_");
                msg += strs[0];
                code += strs[1];
            }
        }
        if(record[sectionCount] != "")
        {
            msg = record[sectionCount];
        }
        m_map[code] = msg;
    }
    return m_map;
}

// 生成错误码头文件
void BaseException::generateErrorCodeHFile(const QString &csvPath, const QString &targetPath)
{
    QStringList rows;
    rows<<"#ifndef ERRORCODE_H"<<"#define ERRORCODE_H\n\n";

    ErrorMap errors = parseErrorCode(csvPath);
    ErrorMap::const_iterator iter = errors.constBegin();
    while(iter != errors.constEnd())
    {
        // 添加宏
        rows <<QString::fromUtf8("#define EC_%1 \"%1\" //%2").arg(iter.key(),iter.value());
        ++iter;
    }
    rows << "\n\n#endif // ERRORCODE_H";
    FileHelper::writeFile(rows,targetPath);
}

QString BaseException::msg() const
{
    static ErrorMap m_map = BaseException::parseErrorCode(GLOBAL::PATH::ERROR_CODE_PATH);
    QString m = STR("错误（%1）： %2").arg(m_code, m_map[m_code].toLocal8Bit());
    if(m_msg != "")
    {
        m += STR("， 详情： %1").arg(m_msg);
    }
    return m;
}

QString BaseException::code() const
{
    return m_code;
}
