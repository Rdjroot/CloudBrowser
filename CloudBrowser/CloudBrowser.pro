TEMPLATE = subdirs

SUBDIRS += \
    qosbrowser \
    test
msvc{
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}
