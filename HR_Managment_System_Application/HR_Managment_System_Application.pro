QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
<<<<<<< Updated upstream
    auth/account.cpp \
    auth/account_adminview.cpp \
=======
    dashboard.cpp \
>>>>>>> Stashed changes
    dbmanager.cpp \
    auth/login.cpp \
    auth/signup.cpp \
    main.cpp \
    mainloading.cpp \
    mainwindow.cpp \
    nav/navbar.cpp \
    nav/navbar_compact.cpp \

HEADERS += \
<<<<<<< Updated upstream
    auth/account.h \
    auth/account_adminview.h \
=======
    dashboard.h \
>>>>>>> Stashed changes
    dbmanager.h \
    auth/login.h \
    auth/signup.h \
    mainloading.h \
    mainwindow.h \
    nav/navbar.h \
    nav/navbar_compact.h \

FORMS += \
    auth/account.ui \
    auth/account_adminview.ui \
    auth/login.ui \
    auth/signup.ui \
<<<<<<< Updated upstream
    mainloading.ui \
=======
    dashboard.ui \
>>>>>>> Stashed changes
    mainwindow.ui \
    nav/navbar.ui \
    nav/navbar_compact.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../database.db

RESOURCES +=
assests.qrc
addFiles.sources = database.db
addFiles.path = .
DEPLOYMENT += addFiles
DISTFILES +=

RESOURCES += \
    stylesheet.qrc
