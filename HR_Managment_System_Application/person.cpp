#include "person.h"

Person::Person(int id, QString name, QString surname, QString mail, QString phone, QString street, QString city, QString plz, bool isAdmin, QString gender, QString title) {
    this->name = name;
    this->id = id;
    this->surname = surname;
    this->mail = mail;
    this->phone = phone;
    this->city = city;
    this->plz = plz;
    this->street = street;
    this->isAdmin = isAdmin;
    this->gender = gender;
    this->title = title;
}

Person::~Person() {

}
