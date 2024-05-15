#include "person.h"

person::person(int id, QString name, QString surname, QString mail, QString phone, QString street, QString city, QString plz, QString housenumber) {
    this->setName(name);
    this->setID(id);
    this->setSurname(surname);
    this->setMail(mail);
    this->setPhone(phone);
    this->setStreet(street);
    this->setCity(city);
    this->setPLZ(plz);
    this->setHousenumber(housenumber);
}
