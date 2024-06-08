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
#include "QList"
#pragma once

//TEST
#include "mitarbeiterview.h"

class dbmanager
{
public:
    //QString ist eine bessere Variante von std::string supported UniCode und ist schneller
    dbmanager();
    ~dbmanager();

    bool addMitarbeiter(QString name, QString surname, QString mail, QString phone,QString password);
    bool addMitarbeiterAdresse(QString plz, QString city, QString street);
    bool addMitarbeiter(QString name, QString surname, QString mail, QString phone,QString password,QString street, int plz, QString city, QString gender, QString title);
    Person* login(QString mail, QString password);
    bool createZeiteintrag(QDateTime shiftstart,QDateTime shiftend,QString note, int employeeID);
    QList<Zeiteintrag*> getArbeitszeiten(int employeeID);
    Zeiteintrag** getSpecificArbeitszeiten(int employeeID, Zeiteintrag **array,QDateTime startzeit,QDateTime endzeit);//middleware muss prüfen das startzeit kleiner endzeit
    bool changePassword(int employeeID, QString newPassword);
    int getArbeitsstunden(int employeeID);
    bool editTimeentries(int timeentryId, QDateTime start, QDateTime end, QString note);
    bool submitAbsence(int id, QDateTime start, QDateTime end,QString reason,QString note);

    //TEST
    QList<Person*> persons; //Mitarbeiter werden von SQL Abfrage gespeichert und dann für Mitarbeiterview verwendet
    QVector<Person*> activepersons; //hier auch
    QVector<MitarbeiterView*> mitarbeiter; //und hier extra ein Vektor um dann den Speicher freigeben zu können
    void getAllEmployees();
    void removeAllEmployeesLocal();
    //void getActiveEmployees();

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
