#include "manbuckets.h"

#include <src/bend/dao/daobuckets.h>

Q_GLOBAL_STATIC(ManBuckets,ins);

ManBuckets::ManBuckets(QObject *parent) : QObject(parent)
{
    m_model = new QStandardItemModel(this);
}

ManBuckets *ManBuckets::instance()
{
    return ins();
}

void ManBuckets::setBuckets()
{
    // 设置mock数据
    DaoBuckets dao;
    QList<MyBucket> buckets =  dao.bucketsFromMock(":/test/buckets1.json");
    m_model->setRowCount(buckets.size());
//    m_model->setColumnCount(3);             // 测试文件中是三列
    for(int i =0 ;i < buckets.size(); i++)
    {
        const MyBucket& bucket = buckets[i];
        QModelIndex index0 = m_model->index(i,0);
        m_model->setData(index0, bucket.name);
        // 可以使鼠标放到该数据上显示提示信息
        m_model->setData(index0, QString("存储桶名称： %1").arg(bucket.name),Qt::ToolTipRole);

        QModelIndex index1 = m_model->index(i,1);
        m_model->setData(index1, bucket.location);

        QModelIndex index2 = m_model->index(i,2);
        m_model->setData(index2, bucket.createDate);
    }
    // 默认按时间倒序排序
    m_model->sort(2,Qt::DescendingOrder);
}

QStandardItemModel *ManBuckets::model() const
{
    return m_model;
}

void ManBuckets::setModel(QStandardItemModel *model)
{
    m_model = model;
}
