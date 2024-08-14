#include "src/bend/dao/clouds/daocloudscos.h"
#include <QtTest>
#include "testcos/tst_testcos.h"

TestCos::TestCos(const std::string id, const std::string key) {
    m_id = QString::fromStdString(id);
    m_key = QString::fromStdString(key);
}

TestCos::~TestCos() {}

void TestCos::initTestCase() {
    m_cos.login(m_id,m_key);
}

void TestCos::cleanupTestCase() {}

void TestCos::test_bucket() {
    std::cout <<"Running!!!!!!!!!!!!!! "<<std::endl;
    QList<MyBucket> bs = m_cos.buckets();
    QVERIFY(bs.size() > 0);
    QCOMPARE(bs.size(), 1);
}


