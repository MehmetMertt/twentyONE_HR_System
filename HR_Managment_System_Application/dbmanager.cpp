#include "dbmanager.h"
#include <QCryptographicHash>
#include "zeiteintrag.h"
#include "person.h"
#include <QVariant>

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
    qDebug() << "Das PW lautet: " << pw;
    query.prepare("SELECT e.id, name, surname, mail, phone, street, city, plz,admin, g.gender, e.title from EMPLOYEE as e JOIN GENDERS as g on e.gender = g.id JOIN ADDRESS as a on e.adressid = a.id WHERE mail = :mail && password = :password");
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
        int admin = query.value(8).toInt();
        QString gender = query.value(9).toString();
        QString title = query.value(10).toString();
        Person * p = new Person(id,name,surname,mail,phone,street,city,plz,admin,gender, title);
        qDebug() << admin;
        qDebug() << gender;
        qDebug() << "Einloggen war erfolgreich " + QString::number(id);
        return p;
    } else {
        sucess = false; //mit dieser local variable wird fett gar nichts gemacht
        qDebug() << "Einloggen war NICHT erfolgreich";
    }
    return nullptr;
}


int dbmanager::getAddressID(int employeeID){
    QSqlQuery query;
    bool sucess;
    query.prepare("SELECT adressid from EMPLOYEE where id = :employeeID");
    query.bindValue(":employeeID",employeeID);

    if(query.exec() && query.size() > 0){
        query.next();
        int id = query.value(0).toInt();
        return id;
    } else {
        sucess = false;
        qDebug() << "getAddressID war NICHT erfolgreich";
    }
    return -1;
}

int dbmanager::getUserIDByMail(QString oldMail){
    QSqlQuery query;
    bool sucess;
    query.prepare("SELECT id from EMPLOYEE where mail = :oldMail");
    query.bindValue(":oldMail",oldMail);

    if(query.exec() && query.size() > 0){
        query.next();
        int id = query.value(0).toInt();
        return id;
    } else {
        sucess = false;
        qDebug() << "getID war NICHT erfolgreich: oldmail: " << oldMail;
    }
    return -1;
}


bool dbmanager::editMitarbeiter(int employeeID,QString name, QString surname, QString mail, QString phone, QString password, QString address, int plz, QString city, QString gender, QString title) {
    bool success = false;
    QSqlQuery queryEmployee;
    QSqlQuery queryAddress;

    int userId = employeeID; // Example user ID

    // Start building the query
    QString employeeQueryString("UPDATE EMPLOYEE SET ");
    QStringList employeeSetters;
    QVariantList employeeValues;
    QString addressQueryString("UPDATE ADDRESS SET ");
    QStringList addressSetters;
    QVariantList addressValues;

    // Check each parameter and add to the query if it's not the default value
    if (!name.isEmpty()) {
        employeeSetters.append("name =?");
        employeeValues.append(name);
    }
    if (!surname.isEmpty()) {
        employeeSetters.append("surname =?");
        employeeValues.append(surname);
    }
    if (!mail.isEmpty()) {
        employeeSetters.append("mail =?");
        employeeValues.append(mail);
    }
    if (!phone.isEmpty()) {
        employeeSetters.append("phone =?");
        employeeValues.append(phone);
    }
    if (!password.isEmpty()) {
        changePassword(userId,password);
    }

    if (!gender.isEmpty()) {
        employeeSetters.append("gender =?");
        int genderid = 1;
        if(gender == "Herr"){
            genderid = 1;
        }
        if(gender == "Frau"){
            genderid = 2;
        }
        if(gender == "Divers"){
            genderid = 3;
        }
        employeeValues.append(genderid);
    }
    if (!title.isEmpty()) {
        employeeSetters.append("title =?");
        employeeValues.append(title);
    }
    if (!address.isEmpty()) {
        addressSetters.append("street =?");
        addressValues.append(address);
    }
    if (plz != 0) {
        addressSetters.append("plz =?");
        addressValues.append(plz);
    }
    if (!city.isEmpty()) {
        addressSetters.append("city =?");
        addressValues.append(city);
    }

    // Combine all setters with commas
    employeeQueryString += employeeSetters.join(", ") + " WHERE id =?"; // Assuming 'id' is the column name for the user's unique identifier
    employeeValues.append(userId);

    // Prepare and execute the query
    queryEmployee.prepare(employeeQueryString);

    // Bind values individually using addBindValue
    foreach (const QVariant &value, employeeValues) {
        queryEmployee.addBindValue(value);
    }

    if (queryEmployee.exec()) {
        success = true;
        qDebug() << "Employee Tabelle Edit erfolgreich";
    } else {
        qDebug() << "Employee Tabelle Edit fehlgeschlagen: " << queryEmployee.lastError();
    }

    if(success == false){
        return success;
    }

    int addressid = getAddressID(userId);

    qDebug() << "Address ID: " << addressid;

    addressQueryString += addressSetters.join(", ") + " WHERE id =?"; // Assuming 'id' is the column name for the user's unique identifier
    addressValues.append(addressid);

    queryAddress.prepare(addressQueryString);

    // Bind values individually using addBindValue
    foreach (const QVariant &value, addressValues) {
        queryAddress.addBindValue(value);
    }

    if (queryAddress.exec()) {
        success = true;
        qDebug() << "Address Tabelle Edit erfolgreich";
    } else {
        qDebug() << "Address Tabelle Edit fehlgeschlagen: " << queryAddress.lastError();
    }


    return success;
}




bool dbmanager::addMitarbeiter(QString name, QString surname, QString mail, QString phone,QString password,QString address, int plz, QString city, QString gender, QString title){
    bool success = false;
    QSqlQuery queryAddress;
    QString pw = sha512_hash(password);
    QStringList address_components = address.split(" ");
    QString street = address_components[0];
    queryAddress.prepare("INSERT into ADDRESS (plz, city, street) VALUES(:plz,:city,:street);");
    queryAddress.bindValue(":city",QString("%1").arg(city));
    queryAddress.bindValue(":plz",QString("%1").arg(plz));
    queryAddress.bindValue(":street",QString("%1").arg(street));
    if(queryAddress.exec() == false){
        qDebug() << "inserting adress not working: "
                 << queryAddress.lastError();
        return false;
    }
    QVariant id = queryAddress.lastInsertId();
    Q_ASSERT(id.isValid() && !id.isNull());
    int addressId = id.toInt();

    QSqlQuery queryEmployee;
    int genderId = 0;
    if(gender == "Herr"){ // switch using qstring is illegal...
        genderId = 1;
    } else if(gender == "Frau"){
        genderId = 2;
    } else if(gender == "Divers"){
        genderId = 3;
    } else {
        genderId = 0;
    }


    queryEmployee.prepare("INSERT INTO EMPLOYEE (name, surname, mail, phone, password,adressid,gender,title) VALUES(:name, :surname, :mail, :phone,:password,:addressid,:gender,:title);");

    queryEmployee.bindValue(":name",QString("%1").arg(name));
    queryEmployee.bindValue(":surname",QString("%1").arg(surname));
    queryEmployee.bindValue(":mail",QString("%1").arg(mail));
    queryEmployee.bindValue(":phone",QString("%1").arg(phone));
    queryEmployee.bindValue(":password",QString("%1").arg(pw));
    queryEmployee.bindValue(":addressid",QString("%1").arg(addressId));
    queryEmployee.bindValue(":gender",QString("%1").arg(genderId));
    queryEmployee.bindValue(":title", QString("%1").arg(title));

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
    QString mysqlDateStart = shiftstart.toString("yyyy-MM-dd hh:mm:ss");
    QString mysqlDateEnde = shiftend.toString("yyyy-MM-dd hh:mm:ss");
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

QList<Zeiteintrag*> dbmanager::getArbeitszeiten(int employeeID){

    QSqlQuery query;

    query.prepare("SELECT shiftstart,shiftend, note,id FROM WORKINGHOURS WHERE  employeeid = :employeeid ");
    query.bindValue(":employeeid",QString("%1").arg(employeeID));

    QList<Zeiteintrag*> zeiteintrag_list = {};

    if(query.exec())
    {
        //success = true;
        qDebug() << "getArbeitszeiten success";

        Zeiteintrag* zeiteintrag;

        while (query.next()) {

            QDateTime startzeit = QDateTime::fromString(query.value(0).toString(), Qt::ISODate);
            QDateTime endzeit = QDateTime::fromString(query.value(1).toString(), Qt::ISODate);
            QString notiz = query.value(2).toString();
            int id = query.value(3).toInt();
            double dauer = startzeit.secsTo(endzeit) / 3600.0;

            zeiteintrag = new Zeiteintrag(employeeID, startzeit, endzeit, dauer, notiz, nullptr);
            zeiteintrag->setTimentryId(id);

            zeiteintrag_list.push_back(zeiteintrag);


        }
    }
    else
    {
        qDebug() << "getArbeitszeiten error:"
                 << query.lastError();
        return {};
    }
    return zeiteintrag_list;
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

    this->removeAllEmployeesLocal();

    //Kein SELECT * weil dadurch würden wir das passwort mitholen was man nicht darf
    //Und mit Joins kann man auch die Adresse und Gender holen
    QSqlQuery query("SELECT e.id, name, surname, mail, phone, street, city, plz,admin, g.gender, e.title from EMPLOYEE as e JOIN GENDERS as g on e.gender = g.id JOIN ADDRESS as a on e.adressid = a.id");
    if(query.exec()){
        while (query.next()){
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            QString surname = query.value(2).toString();
            QString mail = query.value(3).toString();
            QString phone = query.value(4).toString();
            QString street = query.value(5).toString();
            QString city = query.value(6).toString();
            QString plz = query.value(7).toString();
            bool admin = query.value(8).toBool();
            QString gender = query.value(9).toString();
            QString title = query.value(10).toString();

            Person *person = new Person(id, name,surname, mail, phone, street, city, plz, admin, gender, title);
            //Person(int id, QString name, QString surname, QString mail, QString phone, QString street, QString city, QString plz, QString housenumber, bool isAdmin,QString anrede);

            this->persons.push_back(person);
        }
    }
}

void dbmanager::removeAllEmployeesLocal() {
    for(auto& person: this->persons) {
        delete person;
    }

    this->persons.clear();
}

void dbmanager::removeAllActiveEmployeesLocal() {
    for(auto& person: this->activepersons) {
        delete person;
    }

    this->activepersons.clear();
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

            Zeiteintrag *zeiteintrag1 = new Zeiteintrag(0,QDateTime::currentDateTime(),QDateTime::currentDateTime(),0,"",nullptr);

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

bool dbmanager::submitAbsence(Antrag* antrag){

    QSqlQuery query;

    query.prepare("INSERT INTO ABSENCE (employeeid, titel, absencestart, absenceend, absencereason, note) VALUES(:employeeID, :titel, :start, :end, :reason, :note) ");

    query.bindValue(":employeeID",QString("%1").arg(antrag->getEmployeeId()));
    query.bindValue(":start",QString("%1").arg(antrag->getStart().toString("yyyy-MM-dd hh:mm")));
    query.bindValue(":end",QString("%1").arg(antrag->getEnde().toString("yyyy-MM-dd hh:mm")));
    query.bindValue(":reason",QString("%1").arg(this->absence_reasons.key(antrag->getReason())));
    query.bindValue(":titel",QString("%1").arg(antrag->getTitel()));
    query.bindValue(":note",QString("%1").arg(antrag->getNotiz()));

    if(query.exec())
    {
        int id = query.lastInsertId().toInt();
        antrag->setId(id);
        qDebug() << "Absence submission success";
        return true;
    }
    else
    {
        qDebug() << "Absence submission error:"
                 << query.lastError();
        return false;
    }
}

void dbmanager::loadAllRequests() {

    QSqlQuery query;

    query.prepare("SELECT * FROM ABSENCE");

}

void dbmanager::loadRequestsByEmployee(int employeeID) {

    qDeleteAll(this->currentEmployee_requests);
    this->currentEmployee_requests.clear();

    QSqlQuery query;

    query.prepare("SELECT a.id, employeeid, titel, absencestart, absenceend, reason.reason, note, status.status FROM ABSENCE as a JOIN ABSENCE_STATUS as status on a.status = status.id JOIN ABSENCE_REASON as reason on a.absencereason = reason.id WHERE employeeid = :employeeID");

    query.bindValue(":employeeID",QString("%1").arg(employeeID));

    if(query.exec()) {
        while(query.next()) {
            int id = query.value(0).toInt();
            QString titel = query.value(2).toString();
            QDateTime start = query.value(3).toDateTime();
            QDateTime ende = query.value(4).toDateTime();
            QString type = query.value(5).toString();
            QString notiz = query.value(6).toString();
            QString status = query.value(7).toString();

            Antrag* antrag = new Antrag(nullptr, id, employeeID, titel, start, ende, type, notiz, status);
            this->currentEmployee_requests.push_back(antrag);
        }
        qDebug() << "Successfully loaded requests: " << this->currentEmployee_requests.size();
    } else {
        qDebug() << "Error loading requests: " << query.lastError();
    }
}

bool dbmanager::editTimeentries(int timeentryId, QDateTime start, QDateTime end, QString note){

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

bool deleteTimeentries(int timeentryID){


    QSqlQuery query;
    query.prepare("DELETE FROM WORKINGHOURS where timeentryID = :timeentryid") ;
    query.bindValue(":timeentryid",QString("%1").arg(timeentryID));

    if(query.exec()){

        return 1;
    }

    return 0;
}


void dbmanager::loadActiveEmployees(){

    removeAllActiveEmployeesLocal();

    QSqlQuery query("SELECT e.id, e.name, e.surname, e.mail, e.phone, street, city, plz,admin, g.gender, e.title from ACTIVE_EMPLOYEE as ae JOIN EMPLOYEE as e on ae.employeeid = e.id JOIN GENDERS as g on e.gender = g.id JOIN ADDRESS as a on e.adressid = a.id");
    if(query.exec()){
        while (query.next()){
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            QString surname = query.value(2).toString();
            QString mail = query.value(3).toString();
            QString phone = query.value(4).toString();
            QString street = query.value(5).toString();
            QString city = query.value(6).toString();
            QString plz = query.value(7).toString();
            bool admin = query.value(8).toBool();
            QString gender = query.value(9).toString();
            QString title = query.value(10).toString();

            Person *person = new Person(id, name,surname, mail, phone, street, city, plz, admin, gender, title);

            this->activepersons.push_back(person);

            qDebug() << this->activepersons.size() << " fetched";
        }
    }else
        qDebug() << "could not fetch employees from database.";
}

bool dbmanager::loadActiveEmployeeCount() {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM ACTIVE_EMPLOYEE");
    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return -1;
    }

    if (query.next()) {
        this->active_persons_count = query.value(0).toInt();
        return query.value(0).toInt();
    } else {
        qDebug() << "Failed to retrieve the result from query";
        return -1;
    }
}


bool dbmanager::addActiveEmployee(int employeeID) {
    QSqlQuery query;

    query.prepare("INSERT INTO `ACTIVE_EMPLOYEE` (`employeeid`) VALUES (:employeeID)");
    query.bindValue(":employeeID", QString("%1").arg(employeeID));

    if(query.exec()) {
        qDebug() << "Add active success";
        return true;
    } else {
        qDebug() << "Add active fail: " << query.lastError();
        return false;
    }
}

bool dbmanager::removeActiveEmployee(int employeeID) {
    QSqlQuery query;

    query.prepare("DELETE FROM `ACTIVE_EMPLOYEE` WHERE employeeid = :employeeID");
    query.bindValue(":employeeID", QString("%1").arg(employeeID));

    if(query.exec()) {
        qDebug() << "Remove active success";
        return true;
    } else {
        qDebug() << "Remove active fail: " << query.lastError();
        return false;
    }
}

void dbmanager::loadGenders(){
    QSqlQuery query;
    query.prepare("SELECT id, gender from GENDERS");

    if(query.exec() && query.size() > 0){
        while(query.next()){
            QString gender = query.value(1).toString();
            this->genders.insert(query.value(0).toInt(), gender);
        }
    }
}

void dbmanager::loadAbsenceReasons(){
    QSqlQuery query;
    query.prepare("SELECT id, reason from ABSENCE_REASON");

    if(query.exec() && query.size() > 0){
        while(query.next()){
            QString reason = query.value(1).toString();
            this->absence_reasons.insert(query.value(0).toInt(), reason);
        }
    }
}


double dbmanager::getArbeitsstundenSpecific( int employeeID){
    QSqlQuery query;
        //Subdate um 1 erstentag dieser Woche zu finden
    query.prepare("SELECT ROUND(SUM(TIMESTAMPDIFF(MINUTE, shiftstart, shiftend) / 60.0), 2) "
                  "FROM WORKINGHOURS "
                  "WHERE employeeid = :employeeid "
                  "AND shiftstart >= SUBDATE(CURDATE(), WEEKDAY(CURDATE()));");
    query.bindValue(":employeeid",QString("%1").arg(employeeID));

    if (query.exec()) {
        if (query.next()) {
            QVariant result = query.value(0);
            if (result.isNull()) {
                qDebug() << "No working hours recorded for this week.";
            } else {
                double totalHours = result.toDouble();
                qDebug() << "Total hours worked this week:" << totalHours;
                return totalHours;
            }
        } else {
            qDebug() << "No records found.";
            return 0;
        }
    } else {
        qWarning() << "Query execution error:" << query.lastError();
        return 0;
    }
    return 0;

}




