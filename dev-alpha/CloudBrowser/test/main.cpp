#include<QTest>
#include <testcos/tst_testcos.h>
#include <testfilehelper/tst_testfilehelper.h>

int main(int argc, char *argv[])
{
    if(argc == 3)   // 执行的时候将参数在命令行处传入，防止秘钥泄漏
    {
        const char* secretId = argv[1];             //处理敏感信息
        const char* secretKey = argv[2];

        // 仅将与测试无关的参数传递给 QTest
        int testArgc = 1;
        char* testArgv[1] = { argv[0] };

        int status = 0;
        {TestFileHelper tc; status |= QTest::qExec(&tc, testArgc, testArgv);}
        {TestCos tc(secretId, secretKey); status |= QTest::qExec(&tc, testArgc, testArgv);}
        return status;
    }
    else
    {
        std::cout << "Usage: test.exe <secretKey1> <secretKey2>" << std::endl;
        int testArgc = 1;
        char* testArgv[1] = { argv[0] };

        int status = 0;
        {TestFileHelper tc; status |= QTest::qExec(&tc, testArgc, testArgv);}
        {TestCos tc; status |= QTest::qExec(&tc, testArgc, testArgv);}
        return 1;
    }
}
