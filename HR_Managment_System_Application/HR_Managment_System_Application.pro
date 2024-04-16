QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    navbar.cpp \
    navbar_compact.cpp \
    signup.cpp

HEADERS += \
    login.h \
    mainwindow.h \
    navbar.h \
    navbar_compact.h \
    signup.h

FORMS += \
    login.ui \
    mainwindow.ui \
    navbar.ui \
    navbar_compact.ui \
    signup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    stylesheet.qrc
