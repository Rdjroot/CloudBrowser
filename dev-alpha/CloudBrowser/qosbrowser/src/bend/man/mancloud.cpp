#include "mancloud.h"
#include "src/middle/manglobal.h"
#include "src/middle/signals/mansignals.h"
#include "src/plugins/manplugin.h"

Q_GLOBAL_STATIC(ManCloud,ins);

ManCloud::ManCloud(QObject *parent) : QObject(parent)
{

}

ManCloud *ManCloud::instance()
{
    return ins();
}

void ManCloud::login(QString secretId, QString secretKey)
{
    QList<MyBucket> buckets = MG->mPlugin->clouds()->login(secretId,secretKey);
    // 回传登录信息
    emit MG->mSignal->bucketsSuccess(buckets);
}
