#include "antrag.h"

Antrag::Antrag(QObject *parent,  int id, int employeeId, QString titel, QDateTime start, QDateTime ende, QString reason, QString notiz, QString status)
    : QObject{parent}
{

    this->setId(id);
    this->setEmployeeId(employeeId);
    this->setTitel(titel);
    this->setStart(start);
    this->setEnde(ende);
    this->setReason(reason);
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

QString Antrag::getTitel() const {
    return titel;
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

QString Antrag::getReason() const {
    return reason;
}

// Setter-Methoden
void Antrag::setId(int id) {
    this->id = id;
}

void Antrag::setEmployeeId(int employeeId) {
    this->employeeId = employeeId;
}

void Antrag::setTitel(const QString &titel) {
    this->titel = titel;
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

void Antrag::setReason(const QString &reason) {
    this->reason = reason;
}
