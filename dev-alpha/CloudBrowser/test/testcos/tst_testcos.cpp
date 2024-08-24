#include "src/bend/dao/clouds/daocloudscos.h"
#include "src/config/exceptions.h"
#include <QtTest>
#include "testcos/tst_testcos.h"
#include <src/helper/filehelper.h>

TestCos::TestCos(const std::string id, const std::string key) {
    m_id = QString::fromStdString(id);
    m_key = QString::fromStdString(key);
}

TestCos::~TestCos() {}

void TestCos::initTestCase() {
    m_cos.login(m_id,m_key);
    FileHelper::writeFile(QStringList()<<"abc"<<"def",m_uploadLocalPath);   // 创建文件
}

void TestCos::cleanupTestCase() {
    QFile::remove(m_uploadLocalPath);       // 结束删除本地文件
}

void TestCos::test_bucket() {
    QList<MyBucket> bs = m_cos.buckets();
    QVERIFY(bs.size() > 0);
    QCOMPARE(bs.size(), 1); // 确实只有一个存储桶
}

void TestCos::test_getBucketLocation()
{
    QString location = m_cos.getBucketLocation("test-1324376513");
    QCOMPARE(location,"ap-chengdu");
}

void TestCos::test_putBucket()
{
    QSKIP("SKIP test_putBucket");       // 使用宏跳过该测试用例
    // 创建存储桶时，必须以-appid为结尾
    QString bucketName = "testcos-1324376513";
    m_cos.putBucket(bucketName, "ap-shanghai");
    bool exists = m_cos.isBucketExists(bucketName);
    QVERIFY(exists);
}

void TestCos::test_deleteBucket()
{
    QSKIP("SKIP test_deleteBucket");
    QString bucketName = "testcos-1324376513";
    QString location = m_cos.getBucketLocation(bucketName);
    m_cos.deleteBucket(bucketName);
    bool exists = m_cos.isBucketExists(bucketName);
    QVERIFY(!exists);
}

void TestCos::test_getObjects()
{
    QSKIP("SKIP test_getObjects");
    QList<MyObject> objList =  m_cos.getObjects(m_bucketName, "");     // 开启qDebug会打印最外层的内容
    QCOMPARE(objList.size(), 2);

    objList = m_cos.getObjects(m_bucketName, "book/");
    QCOMPARE(objList.size(), 3);
}

/**
 * @brief TestCos::test_getObjects2_data
 * 这里手动输入测试数据，也可以使用csv存储数据批量读取
 */
void TestCos::test_getObjects2_data()
{
    // 数据驱动：第一阶段，准备测试数据，函数名称需要`_data`结尾
    QTest::addColumn<QString>("dir");       // 添加列名
    QTest::addColumn<int>("expected");

    QTest::newRow("root") << "" << 2;       // 添加行
    QTest::newRow("subdir") << "book/" <<4;
    QTest::newRow("leaf") <<"book/awz3/" <<1;

}

void TestCos::test_getObjects2()
{
    QSKIP("SKIP test_getObjects2");
    QFETCH(QString ,dir);       //  QFETCH是拿一条一条数据出来的意思
    QFETCH(int, expected);

    QList<MyObject> objList = m_cos.getObjects(m_bucketName, dir);
    QCOMPARE(objList.size(), expected);
}

/**
 * @brief TestCos::test_getObjectError
 * 测试能否抛出预期中的异常
 */
void TestCos::test_getObjectError()
{
    QVERIFY_EXCEPTION_THROWN(
        m_cos.getObjects("file",""),
        BaseException
        );
}

/**
 * @brief TestCos::test_putObject
 * 测试上传文件
 */
void TestCos::test_putObject()
{
    m_cos.putObject(m_bucketName, m_uploadKey, m_uploadLocalPath, nullptr);
    QVERIFY(m_cos.isObjectExists(m_bucketName, m_uploadKey));
}

/**
 * @brief TestCos::test_putObject
 * 测试下载文件
 */
void TestCos::test_getObject()
{
    m_cos.getObject(m_bucketName, m_uploadKey, m_downloadLocalPath,nullptr);
    QVERIFY(QFile::exists(m_downloadLocalPath));
}

void TestCos::test_isBucketExists()
{   
    bool exists = m_cos.isBucketExists("test-1324376513");
    QVERIFY(exists);
}


