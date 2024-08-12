#include "daocloudsmock.h"
#include<iostream>
#include <QThread>


DaoCloudsMock::DaoCloudsMock(const QString &path)
{
    // 将QVariant的内容转换为Json格式
    m_mock = FileHelper::readAllJson(path).toJsonValue();
}

// 把json文件里的数据数组化，每个元素也是一个jsonmap
QList<MyBucket> DaoCloudsMock::buckets()
{
    QList<MyBucket> res;
    QJsonArray arr = m_mock["buckets"].toArray();       // 这里是把json里的数据数组化
    for(int i = 0 ; i < arr.count(); ++i)
    {
        QJsonValue v = arr[i];
        MyBucket bucket;
        bucket.name = v["name"].toString();
        bucket.location = v["location"].toString();
        bucket.createDate = v["create_date"].toString();

        res.append(bucket);
        // qDebug()<< bucket.name << bucket.location<<bucket.createDate;
    }
    return res;
}

// mock调用登录接口
QList<MyBucket> DaoCloudsMock::login(const QString secretId, const QString secretKey)
{
    QThread::sleep(1);
    QJsonArray arr = m_mock["users"].toArray();
    std::cout << "参数：" << secretId.toStdString() <<", " << secretKey.toStdString() <<std::endl;
    // 这里没有获取数据
    for(int i = 0; i < arr.size(); i++)
    {
        QJsonValue v = arr[i];
        // 这里应该是在模拟数据库里的登录信息
        std::cout << "遍历：" << i <<", " << v["secretId"].toString().toStdString() <<", " << v["secretKey"].toString().toStdString()<<std::endl;
        if(secretId == v["secretId"].toString() && secretKey == v["secretKey"].toString())
        {
            return buckets();// 这里没有对应的存储桶，所有用户用的同一个存储桶
        }
    }
    throw QString::fromUtf8("用户名密码错误");
}
