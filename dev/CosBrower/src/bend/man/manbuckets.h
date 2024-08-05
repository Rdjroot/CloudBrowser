#ifndef MANBUCKETS_H
#define MANBUCKETS_H

#include<QObject>
#include<QDebug>
#include<QStandardItemModel>

#define MB ManBuckets::instance()

class ManBuckets : public QObject
{
    Q_OBJECT
public:
    // 为了方便qt宏使用，不放在private中，但不要直接使用构造函数创建对象
    explicit ManBuckets(QObject *parent = nullptr);

    static ManBuckets* instance();      // 单例模型

    void setBuckets();      // 设置存储桶显示(函数实现)

    QStandardItemModel *model() const;          // 获取成员数据

    void setModel(QStandardItemModel *model);      // 设置model

signals:

private:
    QStandardItemModel *m_model = nullptr;
};

#endif // MANBUCKETS_H
