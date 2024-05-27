#include "dbmanager.h"
#include <QCryptographicHash>
#include "zeiteintrag.h"
#include "person.h"
//Konstruktur der dbmanager klasse, ermögicht einssen zentralisierten Zugriff auf die DB
dbmanager::dbmanager() {
    /*
     * The credentials should never ever be implemented like this in deployment!
     */
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
    query.prepare("SELECT e.id, name, surname, mail, phone, street, city, plz, housenumber,admin,t.title from EMPLOYEE as e JOIN TITLES as t on e.title = t.id JOIN ADDRESS as a on e.adressid = a.id WHERE mail = :mail && password = :password");
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
        bool isAdmin = (query.value(9).toInt() == 1 )? true : false;
        QString anrede = query.value(10).toString();
        Person * p = new Person(id,name,surname,mail,phone,street,city,plz,housenumber,isAdmin,anrede);
        qDebug() << isAdmin;
        qDebug() << anrede;
        qDebug() << "Einloggen war erfolgreich " + QString::number(id);
        return p;
    } else {
        sucess = false;
        qDebug() << "Einloggen war NICHT erfolgreich";
    }
    return nullptr;
}

bool dbmanager::addMitarbeiter(QString name, QString surname, QString mail, QString phone,QString password,QString street, int plz, QString city, QString title){
    bool success = false;
    QSqlQuery queryAddress;
    QString pw = sha512_hash(password);
    int housenumber = 4;
    queryAddress.prepare("INSERT into ADDRESS (plz, city, street, housenumber VALUES(:plz,:city,:street,:housenumber);");
    queryAddress.bindValue(":city",QString("%1").arg(city));
    queryAddress.bindValue(":plz",QString("%1").arg(plz));
    queryAddress.bindValue(":street",QString("%1").arg(street));
    queryAddress.bindValue(":housenumber",QString("%1").arg(housenumber));
    if(queryAddress.exec() == false){
        qDebug() << "inserting adress not working: "
                 << queryAddress.lastError();
        return false;
    }
    QVariant id = queryAddress.lastInsertId();
    Q_ASSERT(id.isValid() && !id.isNull());
    int addressId = id.toInt();

    QSqlQuery queryEmployee;
    int titleid = 0;
    if(title == "Herr"){ // switch using qstring is illegal...
        titleid = 1;
    } else if(title == "Frau"){
        titleid = 2;
    } else if(title == "Divers"){
        titleid = 3;
    } else {
        titleid = 0;
    }


    queryEmployee.prepare("INSERT INTO EMPLOYEE (name, surname, mail, phone, password,adressid,title) VALUES(:name, :surname, :mail, :phone,:password,:addressid,:title);");

    queryEmployee.bindValue(":name",QString("%1").arg(name));
    queryEmployee.bindValue(":surname",QString("%1").arg(surname));
    queryEmployee.bindValue(":mail",QString("%1").arg(mail));
    queryEmployee.bindValue(":phone",QString("%1").arg(phone));
    queryEmployee.bindValue(":password",QString("%1").arg(pw));
    queryEmployee.bindValue(":addressid",QString("%1").arg(addressId));
    queryEmployee.bindValue(":title",QString("%1").arg(titleid));

    if(queryEmployee.exec())
    {
        success = true;
        qDebug() << "addEmployee success";
    }
    else
    {
        qDebug() << "addEmployee error: "
                 << queryEmployee.lastError();
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
        //success = true;
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

Zeiteintrag** getSpecificArbeitszeiten(int employeeID, Zeiteintrag **array,QDateTime shiftstart,QDateTime shiftend){

    bool success = false;
    QSqlQuery query;

    query.prepare("SELECT shiftstart,shiftend, note FROM WORKINGHOURS WHERE  employeeid = :employeeid AND (shiftstart BETWEEN :shiftstart AND :shiftend )");
    query.bindValue(":employeeid",QString("%1").arg(employeeID));
    query.bindValue(":shiftstart",QString("%1").arg(shiftstart.toString("yyyy-MM-dd hh:mm:ss")));
    query.bindValue(":shiftend",QString("%1").arg(shiftend.toString("yyyy-MM-dd hh:mm:ss")));

    if(query.exec())
    {
        //success = true;
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

int getArbeitsstunden(int employeeID){

    bool success = false;
    QSqlQuery query;
                                                                                                                                          //Makedate function to get first day of current year
    query.prepare("SELECT SUM(TIMESTAMPDIFF(HOUR,shiftstart,shiftend)) FROM WORKINGHOURS WHERE  employeeid = :employeeid AND shiftstart > MAKEDATE(EXTRACT(YEAR FROM CURDATE()),1))) ") ;
    query.bindValue(":employeeid",QString("%1").arg(employeeID));

    if(query.exec()){

        return query.value(0).toInt();
    }

    return 0;

}


