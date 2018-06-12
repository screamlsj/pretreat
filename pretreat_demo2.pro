#-------------------------------------------------
#
# Project created by QtCreator 2018-04-04T09:42:34
#
#-------------------------------------------------

QT       += core gui
QT       += xml


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pretreat_demo2
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    pretreatdialog.cpp \
    draw.cpp \
    pretreatsetwidget.cpp \
    threshold_widget.cpp \
    showimage.cpp \
    decompose_widget.cpp \
    illuminate_widget.cpp \
    scaleimage_widget.cpp \
    erosionanddilation_widget.cpp \
    mean_widget.cpp \
    emphasize_widget.cpp \
    median_widget.cpp \
    sysfile.cpp

HEADERS += \
        mainwindow.h \
    pretreatdialog.h \
    draw.h \
    pretreatsetwidget.h \
    threshold_widget.h \
    showimage.h \
    decompose_widget.h \
    illuminate_widget.h \
    scaleimage_widget.h \
    erosionanddilation_widget.h \
    mean_widget.h \
    emphasize_widget.h \
    median_widget.h \
    sysfile.h

FORMS += \
        mainwindow.ui \
    pretreatdialog.ui

#includes
INCLUDEPATH += /opt/halcon/include
INCLUDEPATH += /opt/halcon/include/halconcpp

#libs
LIBS        += -L/opt/halcon/lib/x64-linux -lhalconcpp -lhalcon -ldl -lpthread
