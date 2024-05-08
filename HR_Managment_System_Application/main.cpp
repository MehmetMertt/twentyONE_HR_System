#include "mainwindow.h"
//#include "dbmanager.h"
#include <dbaccess.h>

#include <QApplication>

dbmanager* dbZugriff;

int main(int argc, char *argv[])
{

    qputenv("QT_QPA_PLATFORM", "windows:darkmode=0");

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Human Resources Management System");
    w.show();

    //dbZugriff.addMitarbeiter("Mehmet","M","test@gmail.com","06641337","Password");



    return a.exec();
}
