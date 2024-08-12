#ifndef MANCLOUD_H
#define MANCLOUD_H

#include<QObject>
#include<QDebug>
#include<QStandardItemModel>

#define MC ManCloud::instance()

// 处理云存储的接口，单例模式，主要是数据格式（表）
class ManCloud : public QObject
{
    Q_OBJECT
public:
    // 为了方便qt宏使用，不放在private中，但不要直接使用构造函数创建对象
    explicit ManCloud(QObject *parent = nullptr);

    static ManCloud* instance();      // 单例模型

    void setBuckets();      // 设置存储桶显示(函数实现)

    QStandardItemModel *model() const;          // 获取成员数据

    void setModel(QStandardItemModel *model);      // 设置model

    void login(QString secretId, QString secretKey);

signals:

private:
    QStandardItemModel *m_model = nullptr;
};

#endif // MANBUCKETS_H
