#ifndef TEST_FILEHELPER_H
#define TEST_FILEHELPER_H

#include <QtTest>
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

#endif  // TEST_FILEHELPER_H
