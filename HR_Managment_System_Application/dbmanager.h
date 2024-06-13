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
#include "antrag.h"
#pragma once

//TEST
#include "mitarbeiterview.h"

class dbmanager
{
public:
    //QString ist eine bessere Variante von std::string supported UniCode und ist schneller
    dbmanager();
    ~dbmanager();
    bool changeStatusOfRequest(int requestid,int statusId );
    bool deleteRequest(int requestid);

    int getAddressID(int employeeID);
    int getUserIDByMail(QString oldMail);

    bool editMitarbeiter(int employeeID,QString name = "", QString surname = "", QString mail = "", QString phone = "", QString password = "", QString address = "", int plz = -1, QString city = "", QString gender = "", QString title  = "");
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
    bool submitAbsence(Antrag* antrag);
    void loadAllRequests();
    void loadRequestsByEmployee(int employeeID);
    double getArbeitsstundenSpecific( int employeeID);
    bool deleteTimeentries(int timeentryID);
    //TEST
    QList<Person*> persons; //Mitarbeiter werden von SQL Abfrage gespeichert und dann für Mitarbeiterview verwendet
    QList<Person*> activepersons; //hier auch
    int active_persons_count;
    QList<MitarbeiterView*> mitarbeiter; //und hier extra ein Vektor um dann den Speicher freigeben zu können
    QList<Antrag*> requests;
    QList<Antrag*> currentEmployee_requests;
    void getAllEmployees();
    void removeAllEmployeesLocal();
    void removeAllActiveEmployeesLocal();
    bool addActiveEmployee(int employeeID);
    bool removeActiveEmployee(int employeeID);
    void loadActiveEmployees();
    bool loadActiveEmployeeCount();
    QMap<int, QString> genders;
    QMap<int, QString> absence_reasons;
    void loadGenders();
    void loadAbsenceReasons();
    bool delteRequest(int requestid,QString titel);
    bool editRequest(int requestid,QString titel, QDateTime start, QDateTime ende, int absenceReason, QString note);
private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
