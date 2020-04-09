TEMPLATE = app
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        collection.cpp \
        iterator.cpp \
        main.cpp \
        mainwindow.cpp \
        sortingalgorythm.cpp \
        vehicles.cpp

HEADERS += \
    collection.h \
    iterator.h \
    mainwindow.h \
    misc.h \
    sortingalgorythm.h \
    vehicles.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
