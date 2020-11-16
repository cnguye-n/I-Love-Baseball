#-------------------------------------------------
#
# Project created by QtCreator 2020-05-08T11:42:38
#
#-------------------------------------------------

QT       += core gui location qml quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testBaseball
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        ReadInPrograms.cpp \
        add_all_prices.cpp \
        date.cpp \
        date2.cpp \
        graph.cpp \
        main.cpp \
        mainwindow.cpp \
        souvenir.cpp \
        stadium.cpp

HEADERS += \
        ReadInPrograms.h \
        add_all_prices.h \
        container.h \
        date.h \
        date2.h \
        graph.h \
        linkedlist.h \
        mainwindow.h \
        one_d_array.h \
        souvenir.h \
        stadium.h \
        vector.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    testQML.qml

RESOURCES += \
    resource.qrc
