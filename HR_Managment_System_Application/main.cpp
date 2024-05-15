#include "mainwindow.h"
//#include "dbmanager.h"
#include <dbaccess.h>
#include <QApplication>

dbmanager* dbZugriff;
person* currentEmployee;

int main(int argc, char *argv[])
{

    qputenv("QT_QPA_PLATFORM", "windows:darkmode=0");

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Human Resources Management System");
    w.show();



    return a.exec();
}
