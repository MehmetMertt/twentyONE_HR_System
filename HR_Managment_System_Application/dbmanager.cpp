#include "dbmanager.h"

//Konstruktur der dbmanager klasse, ermögicht einssen zentralisierten Zugriff auf die DB
dbmanager::dbmanager(const QString path) {
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("localhost");
    m_db.setDatabaseName("hrmgt");
    m_db.setUserName("admin");
    m_db.setPassword("admin");

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database failed";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

bool dbmanager::addMitarbeiter(QString vorname, QString nachname, QString email, QString telenr){
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT into Mitarber(Vorname, Nachname, Email, Telefonnummer) VALUES(:Vorname, :Nachname, :Email, :Telefonnummer");
    query.bindValue(":Vorname",vorname);
    query.bindValue(":Nachname",nachname);
    query.bindValue(":Email",email);
    query.bindValue(":Telefonnummer",telenr);
    if(query.exec())
    {
        success = true;
        qDebug() << "addMitarbeiter success";
    }
    else
    {
        qDebug() << "addPerson error:"
                 << query.lastError();
    }

    return success;

}
