#ifndef CONFIG_H
#define CONFIG_H
#include<QString>
#include<QDir>
#include "src/helper/filehelper.h"
#include<QStringList>

// 全局常量
namespace GLOBAL {
    namespace NET {
        static const QString HOST = "localhost";        // 暂时使用本地数据库，之后看情况迁移
        static const QString PORT = "";                 // 暂时空着，通常默认3306
    };

    namespace DATA {
        static const QString DATABASE = "CosBrower";                // 数据库名
        static const QString TB_LOGIN_INFO = "login_info";           // 用户表
    };

    // 数据库登录名和账号
    namespace USER {
        static const QString DEVNAME = "dev_user";     // 开发账号
        static const QString PASSWORD = "aptx4869";           // 密码
    };

    // 执行sql
    namespace SQL {
        static const QString LOGIN_INFO_CREATE = ":/static/sql/login_info.sql";     // 创建表
    };

    // 版本号
    namespace VERSION {
        static const QString MAJOR_CUSTOM = "custom";
        static const QString MAJOR_BUSINESS = "business";
        static const QString JSON_PATH = ":/static/versions/config_default.json";       // 存储版本号的路径
    };

    // 开发/测试/发布
    namespace ENV {
        static const QString ENV_DEV= "dev";
        static const QString ENV_ALPHA = "alpha";
        static const QString ENV_BETA = "beta";
        static const QString ENV_PRE = "pre";
        static const QString ENV_PROD = "prod";
    };

    // 常用路径
    namespace PATH{
        static const QString WORK = QDir::currentPath();
        static const QString TMP = FileHelper::joinPath(WORK, "temp");
        static const QString LOG_DIR = FileHelper::joinPath(QDir::tempPath(), "qos/logs");      // 拼接日志目录
        static const QString ERROR_CODE_PATH = ":/static/docs/errorcode.csv";       // 错误代码csv
    }

    // 日志级别
    enum LOG_LEVEL {
        TOTAL = 0,
        DEBUG = 1,
        INFO = 2,
        WARNING = 3,
        ERROR = 4,
        FATAL = 5
    };

    // 登录名列表
    static const QStringList LOG_NAMES
        = QStringList() << "TOTAL" << "DEBUG" << "INFO" << "WARNING" <<"ERROR" <<"FATAL";

}

#endif // CONFIG_H
