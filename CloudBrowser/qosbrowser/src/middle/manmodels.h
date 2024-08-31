#ifndef MANMODELS_H
#define MANMODELS_H

#include "src/middle/models/cloudmodels.h"
#include <QObject>
#include<QStandardItemModel>

/**
 * @brief 桶数据/对象数据 显示在View中的模型
 *
 */
class ManModels : public QObject
{
    Q_OBJECT
public:
    explicit ManModels(QObject *parent = nullptr);
    ~ManModels();
    // 获取桶数据
    QStandardItemModel *modelBuckets() const;
    // 获取对象数据
    QStandardItemModel *modelObjects() const;

private slots:
    /**
     * @brief 设置存储桶显示(函数实现)
     * @param buckets 桶数据列表
     */
    void setBuckets(const QList<MyBucket>& buckets);

    /**
     * @brief 设置对象显示(函数实现)
     * @param objects 对象数据列表
     */
    void setObjects(const QList<MyObject>& objects);

private:
    /**
     * @brief 初始化界面桶表显示
     */
    void initBucketsTable();

    /**
     * @brief 初始化界面对象表显示
     */
    void initObjectsTable();

private:
    QStandardItemModel *m_modelBuckets = nullptr;           // 存储桶表格模型
    QStandardItemModel *m_modelObjects = nullptr;           // 对象表格模型
};

#endif // MANMODELS_H
