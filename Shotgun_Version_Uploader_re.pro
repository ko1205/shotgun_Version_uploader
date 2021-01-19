QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core.cpp \
    elementselector.cpp \
    main.cpp \
    dialog.cpp \
    mainwindow.cpp \
    projectbutton.cpp \
    taskselectorview.cpp

HEADERS += \
    core.h \
    dialog.h \
    elementselector.h \
    mainwindow.h \
    projectbutton.h \
    taskselectorview.h

win32 {
INCLUDEPATH += C:/Python27/include
LIBS += -LC:/Python27/libs\
        -lpython27
}

macx {
INCLUDEPATH += /System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7/
LIBS += -framework Python
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
