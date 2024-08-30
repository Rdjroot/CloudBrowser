#ifndef APIS_H
#define APIS_H

// 对象存储操作API的宏
namespace API {
    namespace LOGIN{
        static const int NORMAL = 1;            // 常规登录
    }

    namespace BUCKETS
    {
        static const int BASE = 100;
        static const int LIST = BASE + 1;   // 获取桶列表
        static const int PUT = BASE + 2;   // 创建桶
        static const int DEL = BASE + 3;   // 删除桶
    }

    namespace OBJECTS
    {
        static const int BASE = 200;
        static const int LIST = BASE + 1;   // 获取对象列表
        static const int GET = BASE + 10;   // 下载对象
        static const int PUT = BASE + 20;   // 上传对象
    }
}

#endif // APIS_H
