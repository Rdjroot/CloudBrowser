#ifndef GLOBALS_H
#define GLOBALS_H
#include "src/helper/filehelper.h"
#include <QDir>
#include <QString>
#include <QStringList>

namespace GLOBAL {
    namespace NET {
        static const QString HOST = "localhost";
        static const QString PORT = "";
    };

    // 本地数据库和表
    namespace DATA {
        static const QString DATABASE = "CosBrower";
        static const QString TB_LOGIN_INFO = "login_info";
    };

    // 连接本地的mysql用户名和password
    namespace USER {
        static const QString DEVNAME = "dev_user";
        static const QString PASSWORD = "123456";
    };

    // 如果表不存在则创建
    namespace SQL {
    static const QString LOGIN_INFO_CREATE =
        ":/static/sql/login_info.sql";
    };

    // 版本号模拟
    namespace VERSION {
        static const QString MAJOR_CUSTOM = "custom";
        static const QString MAJOR_BUSINESS = "business";
        static const QString JSON_PATH =
            ":/static/versions/config_default.json";
    };

    // 运行环境
    namespace ENV {
        static const QString ENV_DEV = "dev";
        static const QString ENV_ALPHA = "alpha";
        static const QString ENV_BETA = "beta";
        static const QString ENV_PRE = "pre";
        static const QString ENV_PROD = "prod";
    };

    // 资源/配置文件路径
    namespace PATH {
        static const QString WORK = QDir::currentPath();
        static const QString TMP = FileHelper::joinPath(WORK, "temp");
        static const QString LOG_DIR =
            FileHelper::joinPath(QDir::tempPath(), "qos/logs");
        static const QString ERROR_CODE_PATH =
            ":/static/docs/errorcode.csv";

        static const QString MAX_PATH1 = ":/static/img/Maximize-1.png";
        static const QString LOGO_PATH = ":/static/img/icontt.png";
        static const QString MAX_HOVER_PATH = ":/static/img/Maximize-2.png";
        static const QString NORMAL_PATH = ":/static/img/Maximize-3.png";
        static const QString NORMAL_HOVER_PATH = ":/static/img/Maximize-4.png";
        static const QString MIN_PATH = ":/static/img/Minimize-1.png";
        static const QString MIN_HOVER_PATH = ":/static/img/Minimize-2.png";

        static const QString QUIT = ":/static/img/Quit-1.png";
        static const QString QUIT_HOVER = ":/static/img/Quit-2.png";
        static const QString TRANS = ":/static/img/Trans-1.png";
        static const QString TRANS_HOVER = ":/static/img/Trans-2.png";

        static const QString BUCKET = ":/static/img/bucket.png";
        static const QString FILE = ":/static/img/file.png";
        static const QString DIR = ":/static/img/dir.png";
    };

    static const QStringList LOG_NAMES = QStringList()
                                         << "TOTAL" << "DEBUG" << "INFO"
                                         << "WARNING" << "ERROR" << "FATAL";
    enum LOG_LEVEL {
        TOTAL = 0,
        DEBUG = 1,
        INFO = 2,
        WARNING = 3,
        ERROR_L = 4,
        FATAL = 5
    };

};
#endif // GLOBALS_H
