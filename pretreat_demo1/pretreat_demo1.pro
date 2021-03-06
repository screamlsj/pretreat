#-------------------------------------------------
#
# Project created by QtCreator 2018-03-07T09:55:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pretreat_demo1
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
        pretreat.cpp \
    thesholdinputdialog.cpp \
    scaleinputdialog.cpp \
    decomposedialog.cpp \
    geometrictransdialog.cpp \
    affinetransdialog.cpp \
    comparedialog.cpp \
    emphasizedialog.cpp \
    scalemaxdialog.cpp \
    illuminatedialog.cpp

HEADERS += \
        pretreat.h \
    thesholdinputdialog.h \
    scaleinputdialog.h \
    decomposedialog.h \
    geometrictransdialog.h \
    affinetransdialog.h \
    comparedialog.h \
    emphasizedialog.h \
    scalemaxdialog.h \
    illuminatedialog.h

FORMS += \
        pretreat.ui \
    thesholdinputdialog.ui \
    scaleinputdialog.ui \
    decomposedialog.ui \
    geometrictransdialog.ui \
    affinetransdialog.ui \
    comparedialog.ui \
    emphasizedialog.ui \
    scalemaxdialog.ui \
    illuminatedialog.ui

#includes
INCLUDEPATH += /opt/halcon/include
INCLUDEPATH += /opt/halcon/include/halconcpp

#libs
LIBS        += -L/opt/halcon/lib/x64-linux -lhalconcpp -lhalcon -ldl -lpthread
