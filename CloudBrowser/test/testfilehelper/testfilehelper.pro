QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
msvc{
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}
TEMPLATE = app

SOURCES +=  tst_testfilehelper.cpp \
    ../../qosbrowser/src/helper/filehelper.cpp

INCLUDEPATH += $$PWD/../../qosbrowser

RESOURCES += \
    resource.qrc

HEADERS += \
    ../../qosbrowser/src/helper/filehelper.h
