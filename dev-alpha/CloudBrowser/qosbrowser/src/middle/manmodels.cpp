#include "manmodels.h"
#include "src/bend/dao/clouds/daoclouds.h"
#include "src/middle/manglobal.h"
#include "src/middle/models/cloudmodels.h"
#include "src/middle/signals/mansignals.h"
#include "src/plugins/manplugin.h"

#include <src/helper/bytehelper.h>

ManModels::ManModels(QObject *parent)
    : QObject{parent}
{
    m_modelBuckets = new QStandardItemModel(this);
    m_modelObjects = new QStandardItemModel(this);
    initBucketsTable();
    initObjectsTable();

    // 设置存储桶
    connect(MG->mSignal,&ManSignals::bucketsSuccess,this, &ManModels::setBuckets);
    connect(MG->mSignal, &ManSignals::objectsSuccess, this, &ManModels::setObjects);
}

QStandardItemModel *ManModels::modelBuckets() const
{
    return m_modelBuckets;
}

QStandardItemModel *ManModels::modelObjects() const
{
    return m_modelObjects;
}

/**
 * @brief 设置界面的存储桶数据
 * @param buckets  存储桶表格
 */
void ManModels::setBuckets(const QList<MyBucket>& buckets)
{
    m_modelBuckets->setRowCount(buckets.size());           // 设置行数

    for(int i =0 ;i < buckets.size(); i++)
    {
        const MyBucket& bucket = buckets[i];
        QModelIndex index0 = m_modelBuckets->index(i,0);
        m_modelBuckets->setData(index0, bucket.name);
        // 可以使鼠标放到该数据上显示提示信息
        m_modelBuckets->setData(index0, QString::fromLocal8Bit("存储桶名称： %1").arg(bucket.name),
                                Qt::ToolTipRole);
        m_modelBuckets->setData(index0, QIcon(GLOBAL::PATH::BUCKET), Qt::DecorationRole);

        QModelIndex index1 = m_modelBuckets->index(i,1);           // 设置行列数
        m_modelBuckets->setData(index1, bucket.location);          // 行列数和数据内容

        QModelIndex index2 = m_modelBuckets->index(i,2);
        m_modelBuckets->setData(index2, bucket.createDate);
    }
    // 默认按时间倒序排序
    m_modelBuckets->sort(2,Qt::DescendingOrder);

}

/**
 * @brief 设置界面的对象数据
 * @param buckets  对象表格
 */
void ManModels::setObjects(const QList<MyObject> &objects)
{
    m_modelObjects->setRowCount(objects.size());
    for(int i = 0; i < objects.size(); ++i)
    {
        const MyObject &obj = objects[i];
        // 对象(文件)名称
        QModelIndex index0 = m_modelObjects->index(i,0);
        m_modelObjects->setData(index0, obj.name);
        QVariant var;
        var.setValue(obj);
        // Qt::UserRole，将特定的自定义数据与某个模型项关联
        // 这些数据不会被 Qt 的内置视图组件直接使用
        m_modelObjects->setData(index0, var, Qt::UserRole);

        // 设置图标，文件夹是文件夹，文件是文件
        if(obj.isDir())
        {
            m_modelObjects->setData(index0, QIcon(GLOBAL::PATH::DIR), Qt::DecorationRole);
        }
        else
        {
            m_modelObjects->setData(index0, QIcon(GLOBAL::PATH::FILE), Qt::DecorationRole);
        }

        // 大小
        QModelIndex index1 = m_modelObjects->index(i, 1);
        QString sizeStr = ByteHelper::toBeautifulStr(obj.size);
        m_modelObjects->setData(index1, sizeStr);
        // 修改时间
        QModelIndex index2 = m_modelObjects->index(i,2);
        m_modelObjects->setData(index2, obj.lastmodified);
    }
}

/**
 * @brief 初始化表格的title和列数
 */
void ManModels::initBucketsTable()
{
    QStringList labels;
    labels << QString::fromLocal8Bit("桶名称")
           << QString::fromLocal8Bit("地区")
           << QString::fromLocal8Bit("创建时间");

    m_modelBuckets->setColumnCount(labels.size());
    m_modelBuckets->setHorizontalHeaderLabels(labels);
}

void ManModels::initObjectsTable()
{
    // 设置标题内容
    QStringList labels;
    labels << QString::fromLocal8Bit("对象名称") << QString::fromLocal8Bit("大小")
           << QString::fromLocal8Bit("更新时间");
    m_modelObjects->setColumnCount(labels.size());
    m_modelObjects->setHorizontalHeaderLabels(labels);
}
