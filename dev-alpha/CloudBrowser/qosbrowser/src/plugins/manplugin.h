#ifndef MANPLUGIN_H
#define MANPLUGIN_H

#include <QObject>
#include "src/bend/dao/clouds/daoclouds.h"
#include "src/bend/dao/clouds/daocloudsmock.h"
#include "src/bend/dao/configs/version.h"
#include "src/bend/dao/configs/versionjson.h"
#include "src/config/global.h"

class Version;
class DaoClouds;
using namespace GLOBAL;


// 管理全局的插件
class ManPlugin : public QObject
{
    Q_OBJECT
public:
    explicit ManPlugin(QObject *parent = nullptr);
    ~ManPlugin();

    DaoClouds *clouds() const;

    void installPlugins(int argc, char *argv[]);

signals:

private:
    DaoClouds* m_clouds;        // 不能使用派生类作为它的类型
    Version* m_version;
};

#endif // MANPLUGIN_H
