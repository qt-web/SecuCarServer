QT += core
QT += sql
QT += network
QT -= gui

CONFIG += c++11
QTPLUGIN += qsqlmysql

TARGET = SecuCarServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  main.cpp\
            myhttpserver.cpp\
            logger.cpp\
            DBRecords/userrecord.cpp \
            DBRecords/devicerecord.cpp \
            DBRecords/samplerecord.cpp \
            DBRecords/trackrecord.cpp \
    DBManagers/userarray.cpp \
    databasedriver.cpp



HEADERS += \
            myhttpserver.h\
            logger.h\
            DBRecords/userrecord.h \
            DBRecords/devicerecord.h \
            DBRecords/samplerecord.h \
            DBRecords/trackrecord.h \
            DBRecords/crecord.h \
            DBManagers/dbmanager.h \
    DBManagers/userarray.h \
    databasedriver.h

INCLUDEPATH += DBRecords
INCLUDEPATH += DBManagers
INCLUDEPATH += ../QttpServer/src
INCLUDEPATH += ../QttpServer/lib/http/qttp
INCLUDEPATH += ../QttpServer/lib/http/include
INCLUDEPATH += ../QttpServer/lib/http/include/native
INCLUDEPATH += ../QttpServer/lib/http-parser
INCLUDEPATH += ../QttpServer/lib/libuv/include
INCLUDEPATH += ../QttpServer/lib/libuv/src
INCLUDEPATH += ../QttpServer/lib/libuv/src/unix/

LIBS += -L$$PWD/../QttpServer/build/out/Debug/ -lqttpserver
INCLUDEPATH += $$PWD/../QttpServer/build/out/Debug
DEPENDPATH += $$PWD/../QttpServer/build/out/Debug
PRE_TARGETDEPS += $$PWD/../QttpServer/build/out/Debug/libqttpserver.a

LIBS += -L$$PWD/../QttpServer/build/out/Debug/ -lgmock_main
INCLUDEPATH += $$PWD/../QttpServer/build/out/Debug
DEPENDPATH += $$PWD/../QttpServer/build/out/Debug
PRE_TARGETDEPS += $$PWD/../QttpServer/build/out/Debug/libgmock_main.a

LIBS += -L$$PWD/../QttpServer/build/out/Debug/ -lgmock
INCLUDEPATH += $$PWD/../QttpServer/build/out/Debug
DEPENDPATH += $$PWD/../QttpServer/build/out/Debug
PRE_TARGETDEPS += $$PWD/../QttpServer/build/out/Debug/libgmock.a

LIBS += -L$$PWD/../QttpServer/build/out/Debug/ -lgtest
INCLUDEPATH += $$PWD/../QttpServer/build/out/Debug
DEPENDPATH += $$PWD/../QttpServer/build/out/Debug
PRE_TARGETDEPS += $$PWD/../QttpServer/build/out/Debug/libgtest.a

LIBS += -L$$PWD/../QttpServer/build/out/Debug/ -lhttp_parser
INCLUDEPATH += $$PWD/../QttpServer/build/out/Debug
DEPENDPATH += $$PWD/../QttpServer/build/out/Debug
PRE_TARGETDEPS += $$PWD/../QttpServer/build/out/Debug/libhttp_parser.a

LIBS += -L$$PWD/../QttpServer/build/out/Debug/ -lnode_native
INCLUDEPATH += $$PWD/../QttpServer/build/out/Debug
DEPENDPATH += $$PWD/../QttpServer/build/out/Debug
PRE_TARGETDEPS += $$PWD/../QttpServer/build/out/Debug/libnode_native.a

LIBS += -L$$PWD/../QttpServer/build/out/Debug/ -luv
INCLUDEPATH += $$PWD/../QttpServer/build/out/Debug
DEPENDPATH += $$PWD/../QttpServer/build/out/Debug
PRE_TARGETDEPS += $$PWD/../QttpServer/build/out/Debug/libuv.a

SOURCES += ../QttpServer/src/action.cpp
SOURCES += ../QttpServer/src/httpdata.cpp
SOURCES += ../QttpServer/src/httpevent.cpp
SOURCES += ../QttpServer/src/httpserver.cpp
SOURCES += ../QttpServer/src/utils.cpp
SOURCES += ../QttpServer/src/httprequest.cpp
SOURCES += ../QttpServer/src/qttp_global.cpp
SOURCES += ../QttpServer/src/httpresponse.cpp
SOURCES += ../QttpServer/src/defaults.cpp
SOURCES += ../QttpServer/src/fileutils.cpp
SOURCES += ../QttpServer/src/httproute.cpp
SOURCES += ../QttpServer/src/httpurl.cpp
SOURCES += ../QttpServer/src/swagger.cpp

SOURCES += ../QttpServer/lib/http/qttp/qttp.cc
SOURCES += ../QttpServer/lib/http/src/crypto.cc
SOURCES += ../QttpServer/lib/http/src/fs.cc
SOURCES += ../QttpServer/lib/http/src/handle.cc
SOURCES += ../QttpServer/lib/http/src/http.cc
SOURCES += ../QttpServer/lib/http/src/loop.cc
SOURCES += ../QttpServer/lib/http/src/net.cc
SOURCES += ../QttpServer/lib/http/src/stream.cc
SOURCES += ../QttpServer/lib/http/src/tcp.cc

SOURCES += ../QttpServer/lib/http-parser/http_parser.c



HEADERS += ../QttpServer/lib/libuv/src/uv-common.h
HEADERS += ../QttpServer/src/action.h
HEADERS += ../QttpServer/src/httpdata.h
HEADERS += ../QttpServer/src/httpevent.h
HEADERS += ../QttpServer/src/httpserver.h
HEADERS += ../QttpServer/src/utils.h
HEADERS += ../QttpServer/src/httprequest.h
HEADERS += ../QttpServer/src/qttp_global.h
HEADERS += ../QttpServer/src/httpresponse.h
HEADERS += ../QttpServer/src/defaults.h
HEADERS += ../QttpServer/src/fileutils.h
HEADERS += ../QttpServer/src/httproute.h
HEADERS += ../QttpServer/src/httpurl.h
HEADERS += ../QttpServer/src/swagger.h
HEADERS += ../QttpServer/lib/http/qttp/qttp.h

HEADERS += ../QttpServer/lib/http/include/native/base.h
HEADERS += ../QttpServer/lib/http/include/native/callback.h
HEADERS += ../QttpServer/lib/http/include/native/crypto.h
HEADERS += ../QttpServer/lib/http/include/native/dev.h
HEADERS += ../QttpServer/lib/http/include/native/error.h
HEADERS += ../QttpServer/lib/http/include/native/events.h
HEADERS += ../QttpServer/lib/http/include/native/fs.h
HEADERS += ../QttpServer/lib/http/include/native/handle.h
HEADERS += ../QttpServer/lib/http/include/native/http.h
HEADERS += ../QttpServer/lib/http/include/native/loop.h
HEADERS += ../QttpServer/lib/http/include/native/native.h
HEADERS += ../QttpServer/lib/http/include/native/net.h
HEADERS += ../QttpServer/lib/http/include/native/stream.h
HEADERS += ../QttpServer/lib/http/include/native/tcp.h
HEADERS += ../QttpServer/lib/http/include/native/text.h
HEADERS += ../QttpServer/lib/http/include/native/utility.h

HEADERS += ../QttpServer/lib/http-parser/http_parser.h

HEADERS += ../QttpServer/lib/libuv/include/android-ifaddrs.h
HEADERS += ../QttpServer/lib/libuv/include/pthread-barrier.h
HEADERS += ../QttpServer/lib/libuv/include/stdint-msvc2008.h
HEADERS += ../QttpServer/lib/libuv/include/tree.h
HEADERS += ../QttpServer/lib/libuv/include/uv-aix.h
HEADERS += ../QttpServer/lib/libuv/include/uv-bsd.h
HEADERS += ../QttpServer/lib/libuv/include/uv-darwin.h
HEADERS += ../QttpServer/lib/libuv/include/uv-errno.h
HEADERS += ../QttpServer/lib/libuv/include/uv.h
HEADERS += ../QttpServer/lib/libuv/include/uv-linux.h
HEADERS += ../QttpServer/lib/libuv/include/uv-os390.h
HEADERS += ../QttpServer/lib/libuv/include/uv-sunos.h
HEADERS += ../QttpServer/lib/libuv/include/uv-threadpool.h
HEADERS += ../QttpServer/lib/libuv/include/uv-unix.h
HEADERS += ../QttpServer/lib/libuv/include/uv-version.h
HEADERS += ../QttpServer/lib/libuv/include/uv-win.h

HEADERS += ../QttpServer/lib/libuv/src/unix/atomic-ops.h
HEADERS += ../QttpServer/lib/libuv/src/unix/internal.h
HEADERS += ../QttpServer/lib/libuv/src/unix/linux-syscalls.h
HEADERS += ../QttpServer/lib/libuv/src/unix/loop-watcher.c
HEADERS += ../QttpServer/lib/libuv/src/unix/pthread-barrier.c
HEADERS += ../QttpServer/lib/libuv/src/unix/pthread-fixes.c
HEADERS += ../QttpServer/lib/libuv/src/unix/spinlock.h
HEADERS += ../QttpServer/lib/libuv/src/unix/thread.c



# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


