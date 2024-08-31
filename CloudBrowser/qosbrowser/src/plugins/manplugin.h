#ifndef MANPLUGIN_H
#define MANPLUGIN_H

#include <QObject>
#include "src/bend/dao/clouds/daoclouds.h"
#include "src/bend/dao/clouds/daocloudsmock.h"
#include "src/bend/dao/configs/version.h"
#include "src/bend/dao/configs/versionjson.h"
#include "src/config/globals.h"

class Version;
class DaoClouds;

/**
 * @brief 管理插件
 *
 * 初始化版本号/类型、云存储接口（选用哪种云）
 *
 */
class ManPlugin : public QObject
{
    Q_OBJECT
public:
    explicit ManPlugin(QObject *parent = nullptr);
    ~ManPlugin();

    /**
     * @brief 获取云对象
     * @return 返回实际派生的云对象
     */
    DaoClouds *clouds() const;

    /**
     * @brief 安装插件（版本获取、日志打印）
     * @param argc  main函数入参数
     * @param argv  main函数入参[]
     */
    void installPlugins(int argc, char *argv[]);

signals:

private:
    DaoClouds* m_clouds;        // 不能使用派生类作为它的类型
    Version* m_version;
};

#endif // MANPLUGIN_H
