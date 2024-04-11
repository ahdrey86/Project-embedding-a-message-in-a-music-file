QT       += core gui
QT += network
QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client_interface.cpp \
    connection_manager.cpp \
    main.cpp \
    connect_setup.cpp \
    auth_window.cpp \
    register_window.cpp \
    windows_manager.cpp

    #clientwidget.cpp \


HEADERS += \
    client_interface.h \
    connection_manager.h \
    connect_setup.h \
    auth_window.h \
    register_window.h \
    #clientwidget.h \
    #ui_clientwidget.h \
    ui_connect_setup.h \
    ui_auth_window.h \
    ui_register_window.h \
    ui_client_interface.h \
    windows_manager.h

FORMS += \
    client_interface.ui \
    connect_setup.ui \
    auth_window.ui \
    register_window.ui
    #clientwidget.ui \



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
