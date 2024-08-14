#ifndef GATEWAY_H
#define GATEWAY_H

#include <QJsonValue>
#include <QObject>

/**
 * @brief 网关类
 * 负责分发、发送数据
 */
class GateWay : public QObject
{
    Q_OBJECT
public:
    explicit GateWay(QObject *parent = nullptr);
    static GateWay* instance();
    void send(int api, const QJsonValue& value);

private:
    void dispach(int api, const QJsonValue& value);
    void apiLogin(const QJsonValue& value);
};

#endif // GATEWAY_H
