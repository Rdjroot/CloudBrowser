#include "testfilehelper/tst_testfilehelper.h"
#include <QtTest>
#include "src/helper/filehelper.h"
#include<QDebug>
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
    QCOMPARE( FileHelper::readAllTxt(":/static/testfile.txt"),"abc");
}

void TestFileHelper::test_joinPath()
{
    QCOMPARE(FileHelper::joinPath("C:\\a\\b","c"),"C:/a/b/c");
}

