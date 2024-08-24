#ifndef TEST_COS_H
#define TEST_COS_H
#include "src/bend/dao/clouds/daocloudscos.h"
#include <QtTest>
#include<string>

class TestCos : public QObject
{
    Q_OBJECT

public:
    TestCos(const std::string id = "default", const std::string key = "default");
    ~TestCos();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_bucket();
    void test_isBucketExists();
    void test_getBucketLocation();
    void test_putBucket();
    void test_deleteBucket();
    void test_getObjects();

    void test_getObjects2_data();
    void test_getObjects2();

    void test_getObjectError();

    void test_putObject();
    void test_getObject();

private :
    DaoCloudsCos m_cos;
    QString m_id;
    QString m_key;

    QString m_bucketName = "test-1324376513";

    QString m_uploadLocalPath = "./upload.txt";
    QString m_downloadLocalPath = "./download.txt";
    QString m_uploadKey = "book/newupload.txt";

};
#endif // TEST_COS_H
