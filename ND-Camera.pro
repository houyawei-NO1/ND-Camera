#-------------------------------------------------
#
# Project created by QtCreator 2022-08-19T16:42:17
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ND-Camera
TEMPLATE = app
RC_FILE += logo.rc

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
    cameraeidget.cpp \
        main.cpp \
    nanduwidget.cpp \
    menubarwid.cpp \
    pushbutton.cpp \
    toolbutton.cpp \
    ndmassegebox.cpp \
    ctipareawid.cpp \
    cstatewid.cpp \
    cdoublebutton.cpp \
    clickedlabel.cpp \
    ledwidget.cpp \
    resultdialog.cpp \
    textwidget.cpp

HEADERS += \
    cameraeidget.h \
    nanduwidget.h \
    menubarwid.h \
    pushbutton.h \
    toolbutton.h \
    ndmassegebox.h \
    ctipareawid.h \
    cstatewid.h \
    cdoublebutton.h \
    clickedlabel.h \
    ledwidget.h \
    resultdialog.h \
    textwidget.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

RESOURCES += \
    res.qrc

DISTFILES += \
    logo.rc


