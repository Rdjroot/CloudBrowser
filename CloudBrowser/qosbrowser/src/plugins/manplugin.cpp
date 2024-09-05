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
    if(m_clouds != nullptr)
        delete m_clouds;
    if(m_version != nullptr)
        delete m_version;

}

void ManPlugin::installPlugins(int argc, char *argv[])
{
    // 添加日志插件
    mLogIns->setLogger(new LoggerQDebug());

    // 如果输入命令行，命令行参数优先级最高，否则直接加载配置文件中的配置信息
    VersionCmd version(argc, argv);
    if(version.isVaild())               // 判断是否命令行方法执行
    {
        m_version = new VersionCmd(argc,argv);
    }
    else
    {
        m_version = new VersionJson(GLOBAL::VERSION::JSON_PATH);
    }
    m_version->setVersion();

    // 安装云存储插件，当前默认为客户版本，即腾讯云
    if(m_version->major()==GLOBAL::VERSION::MAJOR_CUSTOM)
    {
        m_clouds = new DaoCloudsCos();
    }else
    {
        m_clouds = new DaoCloudsMock(":/static/test/business.json");
    }

}

DaoClouds *ManPlugin::clouds() const
{
    return m_clouds;
}
