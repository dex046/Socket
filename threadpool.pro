TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ./base/CCondition.cpp \
    ./base/CJob.cpp \
    ./base/CThread.cpp \
    ./base/CThreadManager.cpp \
    ./base/CThreadMutex.cpp \
    ./base/CThreadPool.cpp \
    ./base/CWorkThread.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    ./base/noncopyable.h \
    ./base/common.h \
    ./base/CCondition.h \
    ./base/CJob.h \
    ./base/CThread.h \
    ./base/CThreadManager.h \
    ./base/CThreadMutex.h \
    ./base/CThreadPool.h \
    ./base/CWorkThread.h

