#ifndef DAOCLOUDSCOS_H
#define DAOCLOUDSCOS_H

#include "daoclouds.h"
#include <cos_config.h>

class DaoCloudsCos : public DaoClouds
{
public:
    DaoCloudsCos();
    ~DaoCloudsCos();
    QList<MyBucket> buckets()  override;
    QList<MyBucket> login(const QString secretId, const QString secretKey) override;

private:
    qcloud_cos::CosConfig *m_config = nullptr;
};

#endif // DAOCLOUDSCOS_H
