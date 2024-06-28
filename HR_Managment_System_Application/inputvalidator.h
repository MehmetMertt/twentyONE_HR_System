#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <QObject>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QDateTimeEdit>
#include <QDateTime>
#include <QTextEdit>
#pragma once

class InputValidator : public QObject {
    Q_OBJECT

public:
    explicit InputValidator(QWidget *parent = nullptr);

    ~InputValidator(){
        delete Vorname_validator;
        delete Nachname_validator;
        delete Email_validator;
        delete Telefon_validator;
        delete Adresse_validator;
        delete Plz_validator;
        delete Ort_validator;
        delete Passwort_validator;
        delete Titel_validator;
    }

    QValidator *Vorname_validator;
    QValidator *Nachname_validator;
    QValidator *Email_validator;
    QValidator *Telefon_validator;
    QValidator *Adresse_validator;
    QValidator *Plz_validator;
    QValidator *Ort_validator;
    QValidator *Passwort_validator;
    QValidator *Titel_validator;

    // Setter und Getter:
    void setVorname_erlaubt(bool true_false){ Vorname_erlaubt = true_false; }
    bool getVorname_erlaubt(){ return Vorname_erlaubt; }
    void setNachname_erlaubt(bool true_false){ Nachname_erlaubt = true_false; }
    bool getNachname_erlaubt(){ return Nachname_erlaubt; }
    void setEmail_erlaubt(bool true_false){ Email_erlaubt = true_false; }
    bool getEmail_erlaubt(){ return Email_erlaubt; }
    void setTelefon_erlaubt(bool true_false){ Telefon_erlaubt = true_false; }
    bool getTelefon_erlaubt(){ return Telefon_erlaubt; }
    void setAdresse_erlaubt(bool true_false){ Adresse_erlaubt = true_false; }
    bool getAdresse_erlaubt(){ return Adresse_erlaubt; }
    void setPlz_erlaubt(bool true_false){ Plz_erlaubt = true_false; }
    bool getPlz_erlaubt(){ return Plz_erlaubt; }
    void setOrt_erlaubt(bool true_false){ Ort_erlaubt = true_false; }
    bool getOrt_erlaubt(){ return Ort_erlaubt; }
    void setPasswort_erlaubt(bool true_false){ Passwort_erlaubt = true_false; }
    bool getPasswort_erlaubt(){ return Passwort_erlaubt; }
    void setPasswort2_erlaubt(bool true_false){ Passwort_erlaubt = true_false; }
    bool getPasswort2_erlaubt(){ return Passwort_erlaubt; }
    void setDatum_erlaubt(bool true_false){ Datum_erlaubt = true_false; }
    bool getDatum_erlaubt(){ return Datum_erlaubt; }
    void setTitel_erlaubt(bool true_false){ Titel_erlaubt = true_false; }
    bool getTitel_erlaubt(){ return Titel_erlaubt; }

public slots:
    void ueberpruefeVorname(QWidget *);
    void ueberpruefeNachname(QWidget *);
    void ueberpruefeEmail(QWidget *);
    void ueberpruefeTelefon(QWidget *);
    void ueberpruefeAdresse(QWidget *);
    void ueberpruefePlz(QWidget *);
    void ueberpruefeOrt(QWidget *);
    void ueberpruefePasswort(QWidget *);
    void ueberpruefe2Passwort(QWidget *);  //wenns noch ein Passwort gibt, dann heißt es anders als passwort_input deswegen die Funktions ansonsten absturz :/
    void ueberpruefeDatum(QWidget *);
    void ueberpruefeTitel(QWidget *);
    void ueberpruefeNotiz(QWidget *);

private:
    bool Vorname_erlaubt;
    bool Nachname_erlaubt;
    bool Email_erlaubt;
    bool Telefon_erlaubt;
    bool Adresse_erlaubt;
    bool Plz_erlaubt;
    bool Ort_erlaubt;
    bool Passwort_erlaubt;
    bool Passwort2_erlaubt;
    bool Datum_erlaubt;
    bool Titel_erlaubt;
};

#endif // INPUTVALIDATOR_H
