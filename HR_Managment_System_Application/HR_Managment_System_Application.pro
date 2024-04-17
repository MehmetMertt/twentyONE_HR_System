QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dbmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    navbar.cpp \

HEADERS += \
    dbmanager.h \
    mainwindow.h \
    navbar.h \


FORMS += \
    mainwindow.ui \
    navbar.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


DISTFILES += \
    ../database.db \
    Development \

RESOURCES +=
assests.qrc
addFiles.sources = database.db
addFiles.path = .
DEPLOYMENT += addFiles



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../mysql-connector-c++-8.3.0-macos14-arm64/lib64/release/ -lmysqlcppconn8-static
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../mysql-connector-c++-8.3.0-macos14-arm64/lib64/debug/ -lmysqlcppconn8-static
else:unix: LIBS += -L$$PWD/../../mysql-connector-c++-8.3.0-macos14-arm64/lib64/ -lmysqlcppconn8-static

INCLUDEPATH += $$PWD/../../mysql-connector-c++-8.3.0-macos14-arm64/include/jdbc/cppconn
DEPENDPATH += $$PWD/../../mysql-connector-c++-8.3.0-macos14-arm64/include/jdbc/cppconn
