#ifndef CONFIG_H
#define CONFIG_H
#include<QString>
#include<QDir>
#include "src/helper/filehelper.h"

namespace CONF {
    namespace NET {
        static const QString HOST = "localhost";        // 暂时使用本地数据库，之后看情况迁移
        static const QString PORT = "";                 // 暂时空着，通常默认3306
    }

    namespace DATA {
        static const QString DATABASE = "CosBrower";
        static const QString TB_LOGIN_INFO = "login_info";           // 后续会用到
    }

    namespace USER {
        static const QString DEVNAME = "dev_user";     // 开发账号
        static const QString PASSWORD = "aptx4869";           // 密码
    }

    namespace SQL {
        static const QString LOGIN_INFO_CREATE = ":/static/sql/login_info.sql";
    }

//    static bool OK = init();
}

#endif // CONFIG_H
