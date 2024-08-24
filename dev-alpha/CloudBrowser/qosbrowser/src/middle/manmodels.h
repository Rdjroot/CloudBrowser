#ifndef MANMODELS_H
#define MANMODELS_H

#include "src/middle/models/cloudmodels.h"
#include <QObject>
#include<QStandardItemModel>

/**
 * 桶数据/对象数据 显示在View中的模型
 */
class ManModels : public QObject
{
    Q_OBJECT
public:
    explicit ManModels(QObject *parent = nullptr);

    QStandardItemModel *modelBuckets() const;          // 获取桶数据
    QStandardItemModel *modelObjects() const;          // 获取对象数据

signals:

private slots:
    void setBuckets(const QList<MyBucket>& buckets);      // 设置存储桶显示(函数实现)
    void setObjects(const QList<MyObject>& objects);      // 设置存储桶显示(函数实现)

private:
    void initBucketsTable();
    void initObjectsTable();

private:
    QStandardItemModel *m_modelBuckets = nullptr;           // 存储桶表格模型
    QStandardItemModel *m_modelObjects = nullptr;           // 对象表格模型
};

#endif // MANMODELS_H
