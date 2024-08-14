#include "gateway.h"
#include <QtConcurrent>
#include "src/config/apis.h"
#include "src/bend/man/mancloud.h"
#include "src/config/errorcode.h"
#include "src/config/exceptions.h"
#include "src/config/loggerproxy.h"
#include "src/middle/signals/mansignals.h"
#include "src/middle/manglobal.h"

Q_GLOBAL_STATIC(GateWay, ins)

GateWay::GateWay(QObject *parent)
    : QObject{parent}
{}

GateWay *GateWay::instance()
{
    return ins();
}

/**
 * @brief 发送数据
 * @param api  调用的api接口ID
 * @param value  发送内容
 */
void GateWay::send(int api, const QJsonValue &value)
{
    // QtConcurrent实际调用了线程池
    QtConcurrent::run([=](){
        try{
            this->dispach(api,value);
        }
        catch(BaseException e)
        {
            mError(e.msg());
            emit MG->mSignal->error(api,e.msg());
        }
        catch(...){
            BaseException e = BaseException(EC_100000,QString::fromUtf8("未知错误"));
            mError(e.msg());
            emit MG->mSignal->error(api,e.msg());
        }
    });
}

/**
 * @brief 根据api查询路由表，执行任务
 * @param api
 * @param value
 */
void GateWay::dispach(int api, const QJsonValue &value)
{
    switch(api)
    {
        case API::LOGIN::NORMAL:
            apiLogin(value);
        default:
            break;

    }
}
/**
 * @brief 执行登录
 * @param value
 */
void GateWay::apiLogin(const QJsonValue &value)
{
    QString secretId = value["secretId"].toString();
    QString secretKey = value["secretKey"].toString();
    MG->mCloud->login(secretId,secretKey);
    emit MG->mSignal->loginSuccess();            // 发出登录成功信号
}
