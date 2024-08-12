QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    src/bend/dao/daobuckets.cpp \
    src/bend/dao/daologininfo.cpp \
    src/bend/man/manbuckets.cpp \
    src/bend/man/mandb.cpp \
    src/bend/models/dbmodels.cpp \
    src/bend/models/mybucket.cpp \
    src/fend/uicom/breadwidget.cpp \
    src/fend/uicom/keywordedit.cpp \
    src/fend/uicom/pagewidget.cpp \
    src/fend/uidelegates/bucketdelegate.cpp \
    src/fend/uilogin/logindialog.cpp \
    src/fend/uimain/bucketwidget.cpp \
    src/fend/uimain/objectswidget.cpp \
    src/fend/uimain/toolwidget.cpp \
    src/fend/uimain/uimain.cpp \
    src/helper/dbmysql.cpp \
    src/helper/filehelper.cpp

HEADERS += \
    src/bend/dao/daobuckets.h \
    src/bend/dao/daologininfo.h \
    src/bend/man/manbuckets.h \
    src/bend/man/mandb.h \
    src/bend/models/dbmodels.h \
    src/bend/models/mybucket.h \
    src/config/config.h \
    src/fend/uicom/breadwidget.h \
    src/fend/uicom/keywordedit.h \
    src/fend/uicom/pagewidget.h \
    src/fend/uidelegates/bucketdelegate.h \
    src/fend/uilogin/logindialog.h \
    src/fend/uimain/bucketwidget.h \
    src/fend/uimain/objectswidget.h \
    src/fend/uimain/toolwidget.h \
    src/fend/uimain/uimain.h \
    src/helper/dbmysql.h \
    src/helper/filehelper.h

FORMS += \
    src/fend/uicom/breadwidget.ui \
    src/fend/uicom/pagewidget.ui \
    src/fend/uilogin/logindialog.ui \
    src/fend/uimain/bucketwidget.ui \
    src/fend/uimain/objectswidget.ui \
    src/fend/uimain/toolwidget.ui \
    src/fend/uimain/uimain.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc
