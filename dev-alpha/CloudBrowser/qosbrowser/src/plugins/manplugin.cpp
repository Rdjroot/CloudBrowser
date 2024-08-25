#include "manplugin.h"

#include <src/bend/dao/configs/versioncmd.h>
#include "src/config/loggerproxy.h"
#include "src/middle/manglobal.h"
#include <src/bend/dao/logs/loggerqdebug.h>
#include <src/bend/dao/clouds/daocloudscos.h>


ManPlugin::ManPlugin(QObject *parent) : QObject(parent)
{
}

ManPlugin::~ManPlugin()
{
    delete m_clouds;
    delete m_version;
}


/**
 * @brief 安装插件（版本获取、日志打印）
 * @param argc
 * @param argv
 */
void ManPlugin::installPlugins(int argc, char *argv[])
{
    // 如果输入命令行，命令行参数优先级最高，否则直接加载配置文件中的配置信息
    VersionCmd version(argc, argv);
    if(version.isVaild())               // 判断是否命令行方法执行
    {
        m_version = new VersionCmd(argc,argv);
    }
    else
    {
        m_version = new VersionJson(VERSION::JSON_PATH);
    }

    m_version->setVersion();

    // 添加日志插件
    mLogIns->setLogger(new LoggerQDebug());

    // 安装云存储插件
    if(m_version->major()==VERSION::MAJOR_BUSINESS)
    {
        m_clouds = new DaoCloudsCos();
    }else
    {
        m_clouds = new DaoCloudsMock(":/static/test/custom.json");
    }

}

DaoClouds *ManPlugin::clouds() const
{
    return m_clouds;
}
