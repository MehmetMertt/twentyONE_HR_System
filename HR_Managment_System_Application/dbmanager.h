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

class dbmanager
{
public:
    //QString ist eine bessere Variante von std::string supported UniCode und ist schneller
    dbmanager();
    bool addMitarbeiter(QString vorname, QString nachname, QString email, QString telenr,QString passwort);
    bool login(QString email,QString passwort);
    bool createZeiteintrag(QDateTime startzeit,QDateTime endzeit,QString notiz, int mitarbeiterID);
private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
