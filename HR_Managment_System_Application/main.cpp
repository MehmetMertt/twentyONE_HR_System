#include "mainwindow.h"
#include "dbmanager.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Human Resources Management System");
    w.show();

    /*QString dbPath = QCoreApplication::applicationDirPath();
    qDebug() << dbPath;
    QDir databasePath;
    qDebug() << databasePath.currentPath();
    QString path = databasePath.currentPath()+"/database.db"; // Not "myDb.db"
    dbmanager dbZugriff = dbmanager(path);
    dbZugriff.addMitarbeiter("Mehmet","M","test@gmail.com","06641337");*/



    return a.exec();
}
