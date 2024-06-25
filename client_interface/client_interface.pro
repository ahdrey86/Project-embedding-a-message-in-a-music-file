QT       += core gui network
QT += sql
QT -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
#    database.cpp \
    function.cpp \
    main.cpp \
    auth_window.cpp \
    menu_window.cpp \
#    myserver.cpp \
    sha_1.cpp \
    singleclient.cpp \
    stat.cpp \
    task1.cpp \
    task2.cpp

HEADERS += \
    auth_window.h \
#    database.h \
    function.h \
    menu_window.h \
#    myserver.h \
    sha_1.h \
    singleclient.h \
    stat.h \
    task1.h \
    task2.h

FORMS += \
    auth_window.ui \
    menu_window.ui \
    stat.ui \
    task1.ui \
    task2.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
