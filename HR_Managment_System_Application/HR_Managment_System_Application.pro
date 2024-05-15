QT       += core gui sql charts


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    auth/account.cpp \
    auth/account_adminview.cpp \
    dashboard.cpp \
    dbmanager.cpp \
    auth/login.cpp \
    auth/signup.cpp \
    inputvalidator.cpp \
    main.cpp \
    mainloading.cpp \
    mainwindow.cpp \
    nav/navbar.cpp \
    nav/navbar_compact.cpp \
    person.cpp \
    requests.cpp \
    settings.cpp \
    timetracker.cpp \
    zeiteintrag.cpp

HEADERS += \
    auth/account.h \
    auth/account_adminview.h \
    dashboard.h \
    dbaccess.h \
    dbmanager.h \
    auth/login.h \
    auth/signup.h \
    inputvalidator.h \
    mainloading.h \
    mainwindow.h \
    nav/navbar.h \
    nav/navbar_compact.h \
    person.h \
    requests.h \
    settings.h \
    timetracker.h \
    zeiteintrag.h

FORMS += \
    auth/account.ui \
    auth/account_adminview.ui \
    auth/login.ui \
    auth/signup.ui \
    mainloading.ui \
    dashboard.ui \
    mainwindow.ui \
    nav/navbar.ui \
    nav/navbar_compact.ui \
    requests.ui \
    settings.ui \
    timetracker.ui \
    zeiteintrag.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../database.db

RESOURCES +=
assests.qrc
addFiles.path = .
DEPLOYMENT += addFiles
DISTFILES +=

RESOURCES += \
    stylesheet.qrc
