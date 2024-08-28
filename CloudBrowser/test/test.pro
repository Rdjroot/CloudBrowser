QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app
THIRD_DIR = $$PWD/../
include(../qosbrowser/qosbrowser.pri)

SOURCES += \
    main.cpp \
    testcos/tst_testcos.cpp \
    testfilehelper/tst_testfilehelper.cpp

INCLUDEPATH += \
    ../qosbrowser

HEADERS += \
    testcos/tst_testcos.h \
    testfilehelper/tst_testfilehelper.h

RESOURCES += \
    testresource.qrc
