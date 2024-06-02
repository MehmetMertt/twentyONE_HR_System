#ifndef PERSON_H
#define PERSON_H

#include <QTCore/QString>
#include <QString>
#pragma once

class Person
{
public:
    Person(int id, QString name, QString surname, QString mail, QString phone, QString street, QString city, QString plz, QString housenumber, int admin);
    ~Person();

    QString getName(){return this->name;}
    int getID(){return this->id;}
    QString getSurname(){return this->surname;}
    QString getMail(){return this->mail;}
    QString getPhone(){return this->phone;}
    QString getStreet(){return this->street;}
    QString getCity(){return this->city;}
    QString getHousenumber(){return this->housenumber;}
    QString getPLZ(){return this->plz;}
    int getAdmin(){ return this->admin; }
/*  Setter komplett unnötig imo
    void setName(QString name){this->name = name;}
    void setID(int id){this->id = id;}
    void setSurname(QString surname){ this->surname = surname;}
    void setMail(QString mail){ this->mail = mail;}
    void setPhone(QString phone){ this->phone = phone;}
    void setStreet(QString street){ this->street = street;}
    void setCity(QString city){ this->city = city;}
    void setHousenumber(QString housenumber){ this->housenumber = housenumber;}
    void setPLZ(QString plz){ this->plz = plz;}
*/

private:
    QString name;
    QString surname;
    QString mail;
    QString phone;
    QString street;
    QString city;
    QString plz;
    QString housenumber;
    int id;
    int admin;
};

#endif // PERSON_H
