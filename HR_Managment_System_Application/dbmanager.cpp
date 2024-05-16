#include "dbmanager.h"
#include <QCryptographicHash>
#include "zeiteintrag.h"
#include "person.h"
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


Person* dbmanager::login(QString mail, QString password){
    QSqlQuery query;
    bool sucess;
    QString pw = sha512_hash(password);
    qDebug() << pw;
    query.prepare("SELECT e.id, name, surname, mail, phone, street, city, plz, housenumber from EMPLOYEE as e JOIN ADDRESS as a on e.adressid = a.id WHERE mail = :mail && password = :password");
    query.bindValue(":password",QString("%1").arg(pw));
    query.bindValue(":mail",QString("%1").arg(mail));

    if(query.exec() && query.size() > 0){
        query.next();
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString surname = query.value(2).toString();
        QString mail = query.value(3).toString();
        QString phone = query.value(4).toString();
        QString street = query.value(5).toString();
        QString city = query.value(6).toString();
        QString plz = query.value(7).toString();
        QString housenumber = query.value(8).toString();
        Person * p = new Person(id,name,surname,mail,phone,street,city,plz,housenumber);
        qDebug() << "Einloggen war erfolgreich " + QString::number(id);
        return p;
    } else {
        sucess = false;
        qDebug() << "Einloggen war NICHT erfolgreich";
    }
    return nullptr;
}

bool dbmanager::addMitarbeiter(QString name, QString surname, QString mail, QString phone,QString password){
    bool success = false;
    QSqlQuery query;
    QString pw = sha512_hash(password);

    query.prepare("INSERT INTO EMPLOYEE (name, surname, mail, phone, password) VALUES(:name, :surname, :mail, :phone,:password);");
    query.bindValue(":name",QString("%1").arg(name));
    query.bindValue(":surname",QString("%1").arg(surname));
    query.bindValue(":mail",QString("%1").arg(mail));
    query.bindValue(":phone",QString("%1").arg(phone));
    query.bindValue(":password",QString("%1").arg(pw));
    qDebug() << query.lastQuery();

    if(query.exec())
    {
        success = true;
        qDebug() << "addEmployee success";
    }
    else
    {
        qDebug() << "addEmployee error:"
                 << query.lastError();
    }

    return success;

}

bool dbmanager::changePassword(int employeeID, QString newPassword){
    bool success = false;
    QSqlQuery query;
    QString pw = sha512_hash(newPassword);

    query.prepare("UPDATE EMPLOYEE SET EMPLOYEE.password = :newPassword WHERE id = :employeeID;");
    qDebug() << pw;
    query.bindValue(":newPassword",QString("%1").arg(pw));
    query.bindValue(":employeeID",QString("%1").arg(employeeID));
    qDebug() << query.lastQuery();

    if(query.exec())
    {
        success = true;
        qDebug() << "changePassword success";
    }
    else
    {
        qDebug() << "changePassword error:"
                 << query.lastError();
    }

    return success;

}

bool dbmanager::createZeiteintrag(QDateTime shiftstart, QDateTime shiftend, QString note, int employeeID){

    bool success = false;
    QSqlQuery query;
    QString mysqlDateStart = shiftstart.toString("YYYY-mm-dd hh:mm:ss");
    QString mysqlDateEnde = shiftend.toString("YYYY-mm-dd hh:mm:ss");
    query.prepare("INSERT INTO WORKINGHOURS (shiftstart, shiftend,employeeid, note) VALUES(:shiftstart, :shiftend,:employeeid, :note);");
    query.bindValue(":shiftstart",QString("%1").arg(mysqlDateStart));
    query.bindValue(":shiftend",QString("%1").arg(mysqlDateEnde));
    query.bindValue(":note",QString("%1").arg(note));
    query.bindValue(":employeeid",QString("%1").arg(employeeID));



    if(query.exec())
    {
        success = true;
        qDebug() << "createZeiteintrag success";
    }
    else
    {
        qDebug() << "createZeiteintrag error:"
                 << query.lastError();
    }

    return success;


}

Zeiteintrag ** getArbeitszeiten(int employeeID, Zeiteintrag **array ){

    bool success = false;
    QSqlQuery query;

    query.prepare("SELECT shiftstart,shiftend, note FROM WORKINGHOURS WHERE  employeeid = :employeeid ");
    query.bindValue(":employeeid",QString("%1").arg(employeeID));


    if(query.exec())
    {
        success = true;
        qDebug() << "getArbeitszeiten success";

        int i = 0;
        while (query.next()) {

            Zeiteintrag *zeiteintrag1 = new Zeiteintrag(0,QDateTime::currentDateTime(),QDateTime::currentDateTime(),QDateTime::currentDateTime(),0,"",nullptr);

            zeiteintrag1->setStartzeit(QDateTime::fromString(query.value(0).toString(), "yyyy-MM-dd hh:mm:ss"));
            zeiteintrag1->setEndzeit(QDateTime::fromString(query.value(1).toString(), "yyyy-MM-dd hh:mm:ss"));
            zeiteintrag1->setNotiz(query.value(2).toString());

            array[i] = zeiteintrag1;
            ++i;
            qDebug();
        }
    }
    else
    {
        qDebug() << "getArbeitszeiten error:"
                 << query.lastError();
        return 0;
    }

    return array;
}


