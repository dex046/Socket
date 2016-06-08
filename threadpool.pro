TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    CCondition.cpp \
    CJob.cpp \
    CThread.cpp \
    CThreadManager.cpp \
    CThreadMutex.cpp \
    CThreadPool.cpp \
    CWorkThread.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    noncopyable.h \
    common.h \
    CCondition.h \
    CJob.h \
    CThread.h \
    CThreadManager.h \
    CThreadMutex.h \
    CThreadPool.h \
    CWorkThread.h

