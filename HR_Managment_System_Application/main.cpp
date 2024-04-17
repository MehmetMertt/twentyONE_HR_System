#include "mainwindow.h"
#include "dbmanager.h"

#include <QApplication>
#include <../../mysql-connector-c++-8.3.0-macos14-arm64/include/jdbc/cppconn/driver.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QString dbPath = QCoreApplication::applicationDirPath();
    qDebug() << dbPath;
    QDir databasePath;
    qDebug() << databasePath.currentPath();
    QString path = databasePath.currentPath()+"/database.db"; // Not "myDb.db"
    //dbmanager dbZugriff = dbmanager(path);
    //dbZugriff.addMitarbeiter("Mehmet","M","test@gmail.com","06641337");

    try {
        sql::Driver* driver = get_driver_instance();
        std::string host = "localhost";
        std::string user = "root";
        std::string pass = "admin";
        std::string db = "hrmng_database";

        std::unique_ptr<sql::Connection> conn(driver->connect(host, user, pass));
        conn->setAutoCommit(false); // Optional: Control transaction behavior

        // Database operations go here...

        conn->commit(); // Optional: Commit changes

    } catch (sql::SQLException &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;


    }


    w.show();
    return a.exec();
}
