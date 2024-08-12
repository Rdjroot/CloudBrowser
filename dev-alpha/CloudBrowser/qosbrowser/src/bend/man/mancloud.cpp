#include "mancloud.h"

#include "src/bend/dao/clouds/daocloudsmock.h"
#include "src/plugins/manplugin.h"

Q_GLOBAL_STATIC(ManCloud,ins);

ManCloud::ManCloud(QObject *parent) : QObject(parent)
{
    m_model = new QStandardItemModel(this);
}

ManCloud *ManCloud::instance()
{
    return ins();
}

void ManCloud::setBuckets()
{
    // 设置mock数据，json格式
    DaoClouds* dao = MP->clouds();
    QList<MyBucket> buckets =  dao->buckets();      // 一个MyBucket包含一组数据的所有成员数据

    m_model->setRowCount(buckets.size());           // 设置行数

//    m_model->setColumnCount(3);             // 测试文件中是三列

    for(int i =0 ;i < buckets.size(); i++)
    {
        const MyBucket& bucket = buckets[i];

        QModelIndex index0 = m_model->index(i,0);

        m_model->setData(index0, bucket.name);

        // 可以使鼠标放到该数据上显示提示信息
        m_model->setData(index0, QString::fromUtf8("存储桶名称： %1").arg(bucket.name),Qt::ToolTipRole);

        QModelIndex index1 = m_model->index(i,1);           // 设置行列数
        m_model->setData(index1, bucket.location);          // 行列数和数据内容

        QModelIndex index2 = m_model->index(i,2);
        m_model->setData(index2, bucket.createDate);
    }
    // 默认按时间倒序排序
    m_model->sort(2,Qt::DescendingOrder);
}

QStandardItemModel *ManCloud::model() const
{
    return m_model;
}

void ManCloud::setModel(QStandardItemModel *model)
{
    m_model = model;
}

void ManCloud::login(QString secretId, QString secretKey)
{
    // TODO 这里已经获取数据，但还没有返回回去让程序进行登录
    QList<MyBucket> buckets = MP->clouds()->login(secretId,secretKey);
}
