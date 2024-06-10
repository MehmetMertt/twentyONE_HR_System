#include "person.h"

Person::Person(int id, QString name, QString surname, QString mail, QString phone, QString street, QString city, QString plz, QString housenumber, bool isAdmin, QString gender, QString title) {
    this->setName(name);
    this->setID(id);
    this->setSurname(surname);
    this->setMail(mail);
    this->setPhone(phone);
    this->setStreet(street);
    this->setCity(city);
    this->setPLZ(plz);
    this->setHousenumber(housenumber);
    this->setAdmin(isAdmin);
    this->setGender(gender);
    this->setTitle(title);
}

Person::~Person() {

}
