#include "person.h"

Person::Person(int id, QString name, QString surname, QString mail, QString phone, QString street, QString city, QString plz, QString housenumber, int admin) {
    /* unnötig, weil man kanns auch so wie unten machen, was besser ist (unnötiger funktionsaufruf wird sich erspart)
    this->setName(name);
    this->setID(id);
    this->setSurname(surname);
    this->setMail(mail);
    this->setPhone(phone);
    this->setStreet(street);
    this->setCity(city);
    this->setPLZ(plz);
    this->setHousenumber(housenumber);
    */
    this->name = name;
    this->surname = surname;
    this->mail = mail;
    this->phone = phone;
    this->street = street;
    this->city = city;
    this->plz = plz;
    this->housenumber = housenumber;
    this->id = id;
    this->admin = admin;
}

Person::~Person() {

}
