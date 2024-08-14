#ifndef TEST_COS_H
#define TEST_COS_H
#include "src/bend/dao/clouds/daocloudscos.h"
#include <QtTest>
#include<string>

class TestCos : public QObject
{
    Q_OBJECT

public:
    TestCos(const std::string id, const std::string key);
    ~TestCos();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_bucket();
private :
    DaoCloudsCos m_cos;
    QString m_id;
    QString m_key;
};
#endif // TEST_COS_H
