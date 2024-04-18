QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    auth/login.cpp \
    auth/signup.cpp \
    main.cpp \
    mainwindow.cpp \
    nav/navbar.cpp \
    nav/navbar_compact.cpp \

HEADERS += \
    auth/login.h \
    auth/signup.h \
    mainwindow.h \
    nav/navbar.h \
    nav/navbar_compact.h \

FORMS += \
    auth/login.ui \
    auth/signup.ui \
    mainwindow.ui \
    nav/navbar.ui \
    nav/navbar_compact.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    stylesheet.qrc
