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

dbmanager::~dbmanager(){
    for(int i = 0; i < this->mitarbeiter.size(); i++)
        delete this->mitarbeiter[i];
    for(int i = 0; i < this->persons.size(); i++)
        delete this->persons[i];
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
        int admin = query.value(9).toInt();
        
        
        QString anrede = query.value(10).toString();
        Person * p = new Person(id,name,surname,mail,phone,street,city,plz,housenumber,admin,anrede);
        qDebug() << admin;
        qDebug() << anrede;
        qDebug() << "Einloggen war erfolgreich " + QString::number(id);
        return p;
    } else {
        sucess = false; //mit dieser local variable wird fett gar nichts gemacht
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

bool dbmanager::addMitarbeiterAdresse(QString plz, QString city, QString street){
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT INTO ADDRESS (plz, city, street) VALUES(:plz, :city, :street);");
    query.bindValue(":plz",QString("%1").arg(plz));
    query.bindValue(":city",QString("%1").arg(city));
    query.bindValue(":street",QString("%1").arg(street));

    if(query.exec()){
        success = true;
        qDebug() << "addEmployee success";
    }else
        qDebug() << "addEmployee error:"  << query.lastError();

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

    QSqlQuery query;

    query.prepare("SELECT shiftstart,shiftend, note,id FROM WORKINGHOURS WHERE  employeeid = :employeeid ");
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
            zeiteintrag1->setTimentryId(query.value(3).toInt());


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
/*
void dbmanager::getAllEmployees(QVector<Person*> &persons){
    QSqlQuery query("SELECT * FROM EMPLOYEE");
    if(query.exec()){
        while (query.next()){
            int id = query.value(0).toInt();
            QString name = query.value(2).toString();
            QString surname = query.value(3).toString();
            QString mail = query.value(4).toString();
            QString phone = query.value(5).toString();
            QString street = ""; //sind im Ergebnis der query nicht enthalten + aber nötig um ein neues Objekt zu erstellen (Konstruktor), weil
            QString city = "";   //im admindashboard ein Personobjekt benötigt wird
            QString plz = "";
            QString housenumber = "";
            int admin = query.value(1).toInt();
            Person *person = new Person(id, name,surname, mail, phone, street, city, plz, housenumber, admin);

            persons.push_back(person);
        }
    }else
        qDebug() << "could not fetch employees from database.";
}
//*/
void dbmanager::getAllEmployees(){
    QSqlQuery query("SELECT * FROM EMPLOYEE");
    if(query.exec()){
        while (query.next()){
            int id = query.value(0).toInt();
            QString name = query.value(2).toString();
            QString surname = query.value(3).toString();
            QString mail = query.value(4).toString();
            QString phone = query.value(5).toString();
            QString street = ""; //sind im Ergebnis der query nicht enthalten + aber nötig um ein neues Objekt zu erstellen (Konstruktor), weil
            QString city = "";   //im admindashboard ein Personobjekt benötigt wird
            QString plz = "";
            QString housenumber = "";
            int admin = query.value(1).toInt();
            Person *person = new Person(id, name,surname, mail, phone, street, city, plz, housenumber, admin);
            this->persons.push_back(person);
        }
    }
}

Zeiteintrag** getSpecificArbeitszeiten(int employeeID, Zeiteintrag **array,QDateTime shiftstart,QDateTime shiftend){

    bool success = false;
    QSqlQuery query;

    query.prepare("SELECT shiftstart,shiftend,note,id FROM WORKINGHOURS WHERE  employeeid = :employeeid AND (shiftstart BETWEEN :shiftstart AND :shiftend )");
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
            zeiteintrag1->setTimentryId(query.value(3).toInt());

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

    QSqlQuery query;
                                                                                                                                          //Makedate function to get first day of current year
    query.prepare("SELECT SUM(TIMESTAMPDIFF(HOUR,shiftstart,shiftend)) FROM WORKINGHOURS WHERE  employeeid = :employeeid AND shiftstart > MAKEDATE(EXTRACT(YEAR FROM CURDATE()),1))) ") ;
    query.bindValue(":employeeid",QString("%1").arg(employeeID));

    if(query.exec()){

        return query.value(0).toInt();
    }

    return 0;

}

bool submitAbsence(int id, QDateTime start, QDateTime end,QString reason,QString note){


    bool success = false;
    QSqlQuery query;

    query.prepare("INSERT  INTO ABSENCE (employeeid, absencestart,absenceend,absencereason,note) VALUES(:id, :start, :end, :reason, :note) ");

    query.bindValue(":id",QString("%1").arg(id));
    query.bindValue(":start",QString("%1").arg(start.toString("yyyy-MM-dd hh:mm:ss")));
    query.bindValue(":end",QString("%1").arg(end.toString("yyyy-MM-dd hh:mm:ss")));
    query.bindValue(":reason",QString("%1").arg(reason));
    query.bindValue(":note",QString("%1").arg(note));



    if(query.exec())
    {
        success = true;
        qDebug() << "Absence submission success";
        return success;
    }
    else
    {
        qDebug() << "Absence submission error:"
                 << query.lastError();
        return success;
    }


}

bool editTimeentries(int timeentryId, QDateTime start, QDateTime end, QString note){

    bool success = false;
    QSqlQuery query;

    query.prepare("UPDATE WORKINGHOURS SET shiftstart = :start, shiftend = :end, note = :note WHERE id= :id ");
    query.bindValue(":start",QString("%1").arg(start.toString("yyyy-MM-dd hh:mm:ss")));
    query.bindValue(":end",QString("%1").arg(end.toString("yyyy-MM-dd hh:mm:ss")));
    query.bindValue(":note",QString("%1").arg(note));
    query.bindValue(":id",QString("%1").arg(timeentryId));

    if(query.exec())
    {
        success = true;
        qDebug() << "Edit success";
        return success;
    }
    else
    {
        qDebug() << "edit error:"
                 << query.lastError();
        return success;
    }

}

/*
void dbmanager::getActiveEmployees(){
    QSqlQuery query("SELECT * FROM EMPLOYEE where active = 1");
    if(query.exec()){
        while (query.next()){
            int id = query.value(0).toInt();
            QString name = query.value(2).toString();
            QString surname = query.value(3).toString();
            QString mail = query.value(4).toString();
            QString phone = query.value(5).toString();
            QString street = ""; //sind im Ergebnis der query nicht enthalten + aber nötig um ein neues Objekt zu erstellen (Konstruktor), weil
            QString city = "";   //im admindashboard ein Personobjekt benötigt wird
            QString plz = "";
            QString housenumber = "";
            int admin = query.value(1).toInt();
            Person *activeperson = new Person(id, name,surname, mail, phone, street, city, plz, housenumber, admin);

            this->activepersons.push_back(person);
        }
    }else
        qDebug() << "could not fetch employees from database.";
}
*/
