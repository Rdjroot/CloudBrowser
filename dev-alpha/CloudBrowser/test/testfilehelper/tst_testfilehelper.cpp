#include <QtTest>
#include "src/helper/filehelper.h"
#include<QDebug>
// add necessary includes here

class TestFileHelper : public QObject
{
    Q_OBJECT

public:
    TestFileHelper();
    ~TestFileHelper();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_readAllTxt();              // 一个测试用例
    void test_joinPath();
};

TestFileHelper::TestFileHelper()
{

}

TestFileHelper::~TestFileHelper()
{

}

void TestFileHelper::initTestCase()
{

}

void TestFileHelper::cleanupTestCase()
{

}

void TestFileHelper::test_readAllTxt()
{
    QCOMPARE( FileHelper::readAllTxt(":/testfile.txt"),"abc");
}

void TestFileHelper::test_joinPath()
{
    qDebug()<<"这是中文";
    qDebug()<<QString::fromUtf8("qdebug测试内容");

    QCOMPARE(FileHelper::joinPath("C:\\a\\b","c"),"C:/a/b/c");
}

// 这个宏是自动添加的main函数
QTEST_APPLESS_MAIN(TestFileHelper)

#include "tst_testfilehelper.moc"
