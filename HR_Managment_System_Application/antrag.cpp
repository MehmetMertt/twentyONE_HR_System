#include "antrag.h"

Antrag::Antrag(QObject *parent,  int id, int employeeId, QDateTime start, QDateTime ende, QString type, QString notiz, QString status)
    : QObject{parent}
{

    this->setId(id);
    this->setEmployeeId(employeeId);
    this->setStart(start);
    this->setEnde(ende);
    this->setType(type);
    this->setNotiz(notiz);
    this->setStatus(status);

}



// Getter-Methoden
int Antrag::getId() const {
    return id;
}

int Antrag::getEmployeeId() const {
    return employeeId;
}

QDateTime Antrag::getStart() const {
    return start;
}

QDateTime Antrag::getEnde() const {
    return ende;
}

QString Antrag::getNotiz() const {
    return notiz;
}

QString Antrag::getStatus() const {
    return status;
}

QString Antrag::getType() const {
    return type;
}

// Setter-Methoden
void Antrag::setId(int id) {
    this->id = id;
}

void Antrag::setEmployeeId(int employeeId) {
    this->employeeId = employeeId;
}

void Antrag::setStart(const QDateTime &start) {
    this->start = start;
}

void Antrag::setEnde(const QDateTime &ende) {
    this->ende = ende;
}

void Antrag::setNotiz(const QString &notiz) {
    this->notiz = notiz;
}

void Antrag::setStatus(const QString &status) {
    this->status = status;
}

void Antrag::setType(const QString &type) {
    this->type = type;
}
