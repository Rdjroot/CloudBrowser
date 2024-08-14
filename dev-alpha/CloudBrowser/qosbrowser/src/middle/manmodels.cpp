#include "manmodels.h"
#include "src/bend/dao/clouds/daoclouds.h"
#include "src/middle/manglobal.h"
#include "src/middle/models/cloudmodels.h"
#include "src/middle/signals/mansignals.h"
#include "src/plugins/manplugin.h"

ManModels::ManModels(QObject *parent)
    : QObject{parent}
{
    m_model = new QStandardItemModel(this);
    // 设置存储桶
    connect(MG->mSignal,&ManSignals::bucketsSuccess,this, &ManModels::setBuckets);
}

QStandardItemModel *ManModels::model() const
{
    return m_model;
}

/**
 * @brief ManModels::setBuckets 设置界面的存储桶数据
 * @param buckets   用户的所有存储数据
 */
void ManModels::setBuckets(const QList<MyBucket>& buckets)
{
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
