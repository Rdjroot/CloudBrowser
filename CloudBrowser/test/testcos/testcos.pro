QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../third/cos/libs/x64/ -lcossdk
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../third/cos/libs/x64/ -lcossdkd
else:unix: LIBS += -L$$PWD/../../third/cos/libs/x64/ -lcossdk

INCLUDEPATH += $$PWD/../../third/cos/include
DEPENDPATH += $$PWD/../../third/cos/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../third/cos/third_party/lib/x64/poco/ -lPocoFoundation
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../third/cos/third_party/lib/x64/poco/ -lPocoFoundationd
else:unix: LIBS += -L$$PWD/../../third/cos/third_party/lib/x64/poco/ -lPocoFoundation

INCLUDEPATH += $$PWD/../../third/cos/third_party/include
DEPENDPATH += $$PWD/../../third/cos/third_party/include


SOURCES +=  tst_testcos.cpp \
    ../../qosbrowser/src/bend/dao/clouds/daocloudscos.cpp \
    ../../qosbrowser/src/config/exceptions.cpp \
    ../../qosbrowser/src/helper/filehelper.cpp \
    ../../qosbrowser/src/middle/models/cloudmodels.cpp

INCLUDEPATH += \
    ../../qosbrowser

HEADERS += \
    ../../qosbrowser/src/bend/dao/clouds/daoclouds.h \
    ../../qosbrowser/src/bend/dao/clouds/daocloudscos.h \
    ../../qosbrowser/src/config/exceptions.h \
    ../../qosbrowser/src/helper/filehelper.h \
    ../../qosbrowser/src/middle/models/cloudmodels.h

