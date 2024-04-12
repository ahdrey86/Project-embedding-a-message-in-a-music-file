QT += core gui
QT += network
QT += sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database_manager.cpp \
    main.cpp \
    mytcpserver.cpp

HEADERS += \
    database_manager.h \
    mytcpserver.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#Библиотека для работы с аудиофайлами
#INCLUDEPATH += $$QTDIR/include
#LIBS += -L$$[QTDIR]/lib -lsndfile
