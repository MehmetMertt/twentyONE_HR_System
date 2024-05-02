#include "dbmanager.h"

//Konstruktur der dbmanager klasse, ermögicht einssen zentralisierten Zugriff auf die DB
dbmanager::dbmanager(const QString path) {
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("localhost");
    m_db.setDatabaseName("hrmgt_database");
    m_db.setUserName("hrmgt_admin");
    m_db.setPassword("admin");

    if (!m_db.open())
    {
        QString errorMessage = m_db.lastError().text();

        // Display the error message in a more informative way
        qDebug() << "Error: connection with database failed: " << errorMessage;
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

bool dbmanager::login(QString email, QString passwort){
    QSqlQuery query;
    bool sucess;
    query.prepare("SELECT MitarbeiterID from Mitarbeiter WHERE Email = :Email && Passwort = :Passwort");
    query.bindValue(":Passwort",QString("'%1'").arg(email));
    query.bindValue(":Email",QString("'%1'").arg(passwort));
    if(query.exec()){
        sucess = true;
        qDebug() << "Einloggen war erfolgreich";
    } else {
        sucess = false;
        qDebug() << "Einloggen war NICHT erfolgreich";
    }
    return sucess;
}

bool dbmanager::addMitarbeiter(QString vorname, QString nachname, QString email, QString telenr,QString passwort){
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT INTO Mitarbeiter (Vorname, Nachname, Email, Telefonnummer, Passwort) VALUES(:Vorname, :Nachname, :Email, :Telefonnummer,:Passwort);");
    query.bindValue(":Vorname",QString("'%1'").arg(vorname));
    query.bindValue(":Nachname",QString("'%1'").arg(nachname));
    query.bindValue(":Email",QString("'%1'").arg(email));
    query.bindValue(":Telefonnummer",QString("'%1'").arg(telenr));
    query.bindValue(":Passwort",QString("'%1'").arg(passwort));


    qDebug() << query.lastQuery();

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
