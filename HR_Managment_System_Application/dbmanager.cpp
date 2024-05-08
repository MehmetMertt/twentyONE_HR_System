#include "dbmanager.h"
#include <QCryptographicHash>
//Konstruktur der dbmanager klasse, ermögicht einssen zentralisierten Zugriff auf die DB
dbmanager::dbmanager() {
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("localhost");
    m_db.setDatabaseName("hrmgt_database");
    m_db.setUserName("hrmgt_admin");
    m_db.setPassword("admin");

    if (!m_db.open())
    {
        QString errorMessage = m_db.lastError().text();
        qDebug() << "Error: connection with database failed: " << errorMessage;
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

QString sha512_hash(QString pw){
    QByteArray passwortHash = pw.toUtf8();
    QByteArray hash = QCryptographicHash::hash(passwortHash, QCryptographicHash::Sha512);
    return QString(hash.toHex());
}


bool dbmanager::login(QString email, QString passwort){
    QSqlQuery query;
    bool sucess;
    QString pw = sha512_hash(passwort);
    qDebug() << pw;
    query.prepare("SELECT MitarbeiterID from Mitarbeiter WHERE Email = :Email && Passwort = :Passwort");
    query.bindValue(":Passwort",QString("'%1'").arg(pw));
    query.bindValue(":Email",QString("'%1'").arg(email));
    if(query.exec() && query.size() > 0){
        query.next();
        int mitarbeiterID = query.value(0).toInt();
        sucess = true;
        qDebug() << "Einloggen war erfolgreich " + QString::number(mitarbeiterID);
    } else {
        sucess = false;
        qDebug() << "Einloggen war NICHT erfolgreich";
    }
    return sucess;
}

bool dbmanager::addMitarbeiter(QString vorname, QString nachname, QString email, QString telenr,QString passwort){
    bool success = false;
    QSqlQuery query;
    QString pw = sha512_hash(passwort);

    query.prepare("INSERT INTO Mitarbeiter (Vorname, Nachname, Email, Telefonnummer, Passwort) VALUES(:Vorname, :Nachname, :Email, :Telefonnummer,:Passwort);");
    query.bindValue(":Vorname",QString("'%1'").arg(vorname));
    query.bindValue(":Nachname",QString("'%1'").arg(nachname));
    query.bindValue(":Email",QString("'%1'").arg(email));
    query.bindValue(":Telefonnummer",QString("'%1'").arg(telenr));
    query.bindValue(":Passwort",QString("'%1'").arg(pw));
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

bool dbmanager::createZeiteintrag(QDateTime startzeit, QDateTime endzeit, QString notiz, int mitarbeiterID){

    bool success = false;
    QSqlQuery query;
    QString mysqlDateStart = startzeit.toString("YYYY-mm-dd hh:mm:ss");
    QString mysqlDateEnde = endzeit.toString("YYYY-mm-dd hh:mm:ss");
    query.prepare("INSERT INTO Mitarbeiter (Arbeitsbeginn, Arbeitsende,Notiz) VALUES(:Arbeitsbeginn, :Arbeitsende, :Notiz) WHERE MitarbeiterID = : MitarbeiterID ;");
    query.bindValue(":Arbeitsbeginn",QString("'%1'").arg(mysqlDateStart));
    query.bindValue(":Arbeitsende",QString("'%1'").arg(mysqlDateEnde));
    query.bindValue(":Notiz",QString("'%1'").arg(notiz));
    query.bindValue(":MitarbeiterID",QString("'%1'").arg(mitarbeiterID));



    if(query.exec())
    {
        success = true;
        qDebug() << "logZeit success";
    }
    else
    {
        qDebug() << "logZeit error:"
                 << query.lastError();
    }

    return success;


}
