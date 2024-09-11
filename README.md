# CloudBrowser 云存储浏览器
[TOC]

## 项目简介

> 本项目为基于QT5和C++11的云对象存储可视化管理工具

### 什么是云存储

云存储是一种通过互联网将数据存储在远程服务器上的技术。

这种技术使得用户可以在任何时间、任何地点，通过网络访问和管理自己的数据，而不需要依赖本地存储设备。

云存储的主要优势包括可扩展性、数据冗余和备份、易于共享和协作、以及成本效益。

用户可以根据需要选择不同的存储方案，如文件存储、块存储或对象存储，以满足其特定的应用需求

### 什么是对象存储

对象存储是云存储的一种形式，专门设计用于高扩展性和高灵活性的存储需求。对象存储将数据以“对象”的形式存储。

对象（Object）由ID、数据（data）、元数据（metadata）以及属性（attribute）组成。

![image-20240908090146436](https://raw.githubusercontent.com/Rdjroot/Img_beds/master/img/202409080901544.png)

- **对象ID**（唯一标识符）：一个唯一的标识符，用于检索和访问对象。

- **数据（Data）**：实际的存储内容，可以是任何类型的文件或数据块。

- **元数据（Metadata）**：描述对象的数据，包括创建时间、修改时间、权限信息、标签等，帮助系统和用户理解和管理对象。

- **属性（Attributes）**：附加的信息，如存储类、版本控制信息等，这些属性有助于对象的管理和优化。

对象存储相较其他云存储技术相比，效率不算高，通常用于存储——“任何可以被读取但对读取速度没有实际性能限制（要求）的东西”，故而**对象**无数据格式限制。

用户在使用时，使用API与之进行交互，并不直接操作对象。

### 项目：云对象存储浏览器

云对象存储浏览器是针对云对象存储开发的可视化管理工具，实现大框架可对接扩展任何厂商提供的云存储服务，轻松实现对云对象资源的查看和管理。

- 基于对象存储特性，没有目录层级结构，可容纳任何格式数据。
- 支持HTTP/HTTPS协议访问的分布式存储服务，采用异步进行上传/下载对象传输。

- 项目设计采用MVD结构，解耦前后端，易于扩展复用，涵盖了基础的存储桶管理、资源对象管理、文件上传下载，用户管理等功能，
- 兼顾日志、错误码等项目基底功能，具有健壮性。

_涵盖知识：QT，信号与槽，MVC(D)模型，对象树模型，属性系统，元对象系统，qss，数据库，单例模式，异步线程池。_

## 项目结构

![架构图](https://raw.githubusercontent.com/Rdjroot/Img_beds/master/img/202409091521865.png)

<center>项目架构</center>

### 项目目录说明

```makefile
CloudStorage
├─CloudBrowser	# 项目
│  ├─build	# 构建运行目录，本地构建后生成
│  ├─qosbrowser	# 项目源码
│  │  ├─src		# 源码详细结构见下面思维导图
│  │  │  ├─bend		# 后端代码
│  │  │  ├─config	# 配置类代码
│  │  │  ├─fend		# 前端代码
│  │  │  ├─helper	# 工具类代码
│  │  │  ├─middle	# 中间件代码
│  │  │  └─plugins  # 插件代码
│  │  └─static	# 资源文件（如配置json，图片，csv等）
│  ├─test			# 单元测试
│  └─third			# 三方件
│      
├─note imgs   # 笔记图片
├─output	  # 安装包及inno setup脚本
└─packet_static # 用于打包的资源文件
```

### 代码层级

![分层设计](https://raw.githubusercontent.com/Rdjroot/Img_beds/master/img/202409091522281.png)

<center>分层设计</center>

![云对象存储浏览器](https://raw.githubusercontent.com/Rdjroot/Img_beds/master/img/202409091524949.png)

<center>源码分层</center>

## 使用说明

### 安装

使用`output/`目录下的setup安装包，或者在release查看。

### 功能

> 目前仅对接腾讯云厂商。
>
> 亦可使用本地mock数据进行验证。

#### 登录云存储账号

在SecretID和SecretKey填写云服务厂商提供的账户密码。

- 登录名（自定义）用于存储本地登录账户，用于记忆账号密码
- 勾选`记住会话`程序将把账户信息（id、密码、备注）存储到内置数据库中。如果取消勾选，将会从数据库中删除账户信息。

![image-20240910100412333](https://raw.githubusercontent.com/Rdjroot/Img_beds/master/img/202409101004384.png)

#### 创建存储桶

单击存储桶，填写name-id和桶位置来创建存储桶。

![image-20240910103640924](https://raw.githubusercontent.com/Rdjroot/Img_beds/master/img/202409101036991.png)

#### 删除存储桶

仅支持删除空的存储桶，右击存储桶弹出删除按钮

![image-20240910103814606](https://raw.githubusercontent.com/Rdjroot/Img_beds/master/img/202409101038651.png)

![image-20240910103857120](https://raw.githubusercontent.com/Rdjroot/Img_beds/master/img/202409101038167.png)

#### 查看对象

从左侧列表或者中央存储桶表格**双击**对应存储桶进入桶内，（也可以进入目录和退出目录）

![image-20240910103957590](https://raw.githubusercontent.com/Rdjroot/Img_beds/master/img/202409101039647.png)

#### 上传对象

单击`上传`，在本地选择对象打开

![image-20240910104143950](https://raw.githubusercontent.com/Rdjroot/Img_beds/master/img/202409101041013.png)

可在右上角查看传输列表

![image-20240910104325050](https://raw.githubusercontent.com/Rdjroot/Img_beds/master/img/202409101043103.png)

#### 下载对象

选中对象栏，单击`下载`菜单

![image-20240910104426053](https://raw.githubusercontent.com/Rdjroot/Img_beds/master/img/202409101044113.png)

同样可以在右上角传输列表查看下载列表

![image-20240910104544729](https://raw.githubusercontent.com/Rdjroot/Img_beds/master/img/202409101045795.png)

### 日志

日志目录：安装目录下的`tmp/logs/`目录下，按日期分类：

![image-20240909152730480](https://raw.githubusercontent.com/Rdjroot/Img_beds/master/img/202409091527527.png)

### 配置项

1、修改日志输出级别：`default_config.json`文件中的`"log_level"`参数

```makefile
# 级别参考以下，默认WARNING，修改后需要重启
TOTAL = 0,
DEBUG = 1,
INFO = 2,
WARNING = 3,
ERROR_L = 4,
FATAL = 5
```

2、腾讯云配置文件：`cosconfig.json`，字段设置参考以下：

```json
{
"SecretId":"********************************", // sercret_id 替换为用户的 SecretId，建议使用子账号密钥，授权遵循最小权限指引，降低使用风险。子账号密钥获取可参见 https://cloud.tencent.com/document/product/598/37140
"SecretKey":"*******************************", // sercret_key 替换为用户的 SecretKey，建议使用子账号密钥，授权遵循最小权限指引，降低使用风险。子账号密钥获取可参见 https://cloud.tencent.com/document/product/598/37140
"Region":"ap-guangzhou",                // 存储桶地域, 替换为客户存储桶所在地域，可以在COS控制台指定存储桶的概览页查看存储桶地域信息，参见 https://console.cloud.tencent.com/cos5/bucket/ ，关于地域的详情见 https://cloud.tencent.com/document/product/436/6224
"SignExpiredTime":360,              // 签名超时时间, 单位s
"ConnectTimeoutInms":6000,          // connect 超时时间, 单位ms
"ReceiveTimeoutInms":60000,         // recv 超时时间, 单位ms
"UploadPartSize":10485760,          // 上传文件分块大小，1M~5G, 默认为10M
"UploadCopyPartSize":20971520,      // 上传复制文件分块大小，5M~5G, 默认为20M
"UploadThreadPoolSize":5,           // 单文件分块上传线程池大小
"DownloadSliceSize":4194304,        // 下载文件分块大小
"DownloadThreadPoolSize":5,         // 单文件下载线程池大小
"AsynThreadPoolSize":2,             // 异步上传下载线程池大小
"LogoutType":1,                     // 日志输出类型,0:不输出,1:输出到屏幕,2输出到 syslog
"LogLevel":3,                       // 日志级别:1: ERR, 2: WARN, 3:INFO, 4:DBG
"IsDomainSameToHost":false,         // 是否使用专有的 host
"DestDomain":"",                    // 特定 host
"IsUseIntranet":false,              // 是否使用特定ip和端口号
"IntranetAddr":""                   // 特定 ip 和端口号,例如“127.0.0.1:80”
}
```

## 项目扩展

### 厂商变更

本项目`1.0.3版本`当前只配置了腾讯云厂商提供的对象存储服务，如果需要增加/变更别的厂商提供的服务。

需要编辑以下地方：

1. 新厂商API接口继承`DaoClouds`类
2. 在`ManPlugins`类安装插件的代码`installPlugins`中添加/修改创建新的厂商类对象。

### 添加对象存储操作功能（后端）

1. 在`ManCloud`类中添加新的操作函数，根据官方API修改`DaoClouds`及其派生类。

2. 在api.h中添加新的接口宏
3. `gateway.h`中新增网关函数代码。

前端代码请自行扩展。

## 项目版本

version 1.0：完成基础架构及对接腾讯云对象存储，核心组件支持桶的创删操作及对象的上传下载。



---

项目参考及三方件来源：

[1] [腾讯云对象存储C++ SDK文档](https://cloud.tencent.com/document/product/436/12301)

[2] [腾讯云对象存储cos-cpp-sdk 源码地址](https://github.com/tencentyun/cos-cpp-sdk-v5)

