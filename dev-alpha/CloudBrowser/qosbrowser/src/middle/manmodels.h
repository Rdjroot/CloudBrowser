#ifndef MANMODELS_H
#define MANMODELS_H

#include "src/middle/models/cloudmodels.h"
#include <QObject>
#include<QStandardItemModel>

class ManModels : public QObject
{
    Q_OBJECT
public:
    explicit ManModels(QObject *parent = nullptr);

    QStandardItemModel *model() const;          // 获取成员数据

    void setBuckets(const QList<MyBucket>& buckets);      // 设置存储桶显示(函数实现)

signals:

private:
    QStandardItemModel *m_model = nullptr;
};

#endif // MANMODELS_H
