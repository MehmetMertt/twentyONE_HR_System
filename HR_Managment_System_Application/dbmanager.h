#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QtSql>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlQuery>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include "zeiteintrag.h"
#include "person.h"
class dbmanager
{
public:
    //QString ist eine bessere Variante von std::string supported UniCode und ist schneller
    dbmanager();
    bool addMitarbeiter(QString name, QString surname, QString mail, QString phone,QString password);
    Person* login(QString mail, QString password);
    bool createZeiteintrag(QDateTime shiftstart,QDateTime shiftend,QString note, int employeeID);
    Zeiteintrag ** getArbeitszeiten(int employeeID, Zeiteintrag **array );
    bool changePassword(int employeeID, QString newPassword);

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
