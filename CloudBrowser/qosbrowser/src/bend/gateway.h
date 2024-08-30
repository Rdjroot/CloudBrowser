#ifndef GATEWAY_H
#define GATEWAY_H

#include <QJsonValue>
#include <QObject>

/**
 * @brief 网关类
 *
 * 负责分发、发送数据，调用接口
 *
 */
class GateWay : public QObject
{
    Q_OBJECT
public:
    explicit GateWay(QObject *parent = nullptr);
    ~GateWay();

    /**
     * @brief 发送数据
     * @param api  调用的api接口ID
     * @param params  发送内容
     */
    void send(int api, const QJsonValue& params =QJsonValue());

private:
    /**
     * @brief 根据api查询路由表，执行任务
     * @param api   路由表参数
     * @param value 携带数据
     */
    void dispach(int api, const QJsonValue& value);

    /**
     * @brief 执行登录
     * @param value
     */
    void apiLogin(const QJsonValue& value);

    /**
     * @brief 获取桶列表
     * @param params
     */
    void apiGetBuckets(const QJsonValue& params);

    /**
     * @brief 创建桶
     * @param params
     */
    void apiPutBucket(const QJsonValue& params);

    /**
     * @brief 删除存储桶
     * @param params
     */
    void apiDeleteBucket(const QJsonValue& params);

    /**
     * @brief 获取对象列表
     * @param params
     */
    void apiGetObjects(const QJsonValue &params);

    /**
     * @brief 上传对象
     * @param params
     */
    void apiPutObject(const QJsonValue &params);

    /**
     * @brief 下载对象
     * @param params
     */
    void apiDownLoadObject(const QJsonValue &params);
};

#endif // GATEWAY_H
