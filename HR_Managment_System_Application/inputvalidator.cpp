#include "inputvalidator.h"

InputValidator::InputValidator(QWidget *parent) : QObject(parent){

    QRegularExpression RegExp_name("[A-Za-zäöüßÄÖÜ]+");
    this->Vorname_validator = new QRegularExpressionValidator(RegExp_name, this);
    this->Nachname_validator = new QRegularExpressionValidator(RegExp_name, this);
    this->Ort_validator = new QRegularExpressionValidator(RegExp_name, this);

    QRegularExpression RegExp_email("^[a-zA-Z0-9]+(\.[a-zA-Z0-9]+)?@[a-zA-Z0-9]+(\.[a-zA-Z]+)$");
    this->Email_validator = new QRegularExpressionValidator(RegExp_email, this);

    QRegularExpression RegExp_telefon("\\+43[0-9]{1,3}[0-9]{1,8}");
    this->Telefon_validator = new QRegularExpressionValidator(RegExp_telefon, this);

    QRegularExpression RegExp_adresse("^[a-zA-Z-]+\\s?[0-9]+$");
    this->Adresse_validator = new QRegularExpressionValidator(RegExp_adresse, this);

    QRegularExpression RegExp_plz("[0-9]{4}");
    this->Plz_validator = new QRegularExpressionValidator(RegExp_plz, this);

    QRegularExpression RegExp_passwort("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[\\W]).{8,}$");
    this->Passwort_validator = new QRegularExpressionValidator(RegExp_passwort, this);

    Vorname_erlaubt = false;
    Nachname_erlaubt = false;
    Email_erlaubt = false;
    Telefon_erlaubt = false;
    Adresse_erlaubt = false;
    Plz_erlaubt = false;
    Ort_erlaubt = false;
    Passwort_erlaubt = false;
}

void InputValidator::ueberpruefeVorname(QWidget *window){
    setVorname_erlaubt(window->findChild<QLineEdit*>("vorname_input")->hasAcceptableInput());
    if(getVorname_erlaubt() == false){
        window->findChild<QLabel*>("error_text")->setText("Nur Eingabe von Buchstaben möglich.");
    }else{
        window->findChild<QLabel*>("error_text")->setText("");
        //window->findChild<QPushButton*>("button")->setEnabled(true);
    }
}

void InputValidator::ueberpruefeNachname(QWidget *window){
    setNachname_erlaubt(window->findChild<QLineEdit*>("nachname_input")->hasAcceptableInput());
    if(getNachname_erlaubt() == false){
        window->findChild<QLabel*>("error_text")->setText("Nur Eingabe von Buchstaben möglich.");
    }else{
        window->findChild<QLabel*>("error_text")->setText("");
        //window->findChild<QPushButton*>("button")->setEnabled(true);
    }
}

void InputValidator::ueberpruefeEmail(QWidget *window){
    setEmail_erlaubt(window->findChild<QLineEdit*>("email_input")->hasAcceptableInput());
    if(getEmail_erlaubt() == false) {
        window->findChild<QLabel*>("error_text")->setText("Das ist keine gültige Email-Adresse.");
    }else{
        window->findChild<QLabel*>("error_text")->setText("");
        //window->findChild<QPushButton*>("button")->setEnabled(true);
    }
}

void InputValidator::ueberpruefeTelefon(QWidget *window){
    setTelefon_erlaubt(window->findChild<QLineEdit*>("tel_input")->hasAcceptableInput());
    if(getTelefon_erlaubt() == false){
        window->findChild<QLabel*>("error_text")->setText("Die Telefonnummer muss mit +43 beginnen und nur die Eingabe von Zahlen ist erlaubt.");
    }else{
        window->findChild<QLabel*>("error_text")->setText("");
        //window->findChild<QPushButton*>("button")->setEnabled(true);
    }
}

void InputValidator::ueberpruefeAdresse(QWidget *window){
    setAdresse_erlaubt(window->findChild<QLineEdit*>("adresse_input")->hasAcceptableInput());
    if(getAdresse_erlaubt() == false){
        window->findChild<QLabel*>("error_text")->setText("Eine gültige Adresse besteht aus Buchstaben, Zahlen, Beichstrichen und Punkten.");
    }else{
        window->findChild<QLabel*>("error_text")->setText("");
        //window->findChild<QPushButton*>("button")->setEnabled(true);
    }
}

void InputValidator::ueberpruefePlz(QWidget *window){
    setPlz_erlaubt(window->findChild<QLineEdit*>("plz_input")->hasAcceptableInput());
    if(getPlz_erlaubt() == false){
        window->findChild<QLabel*>("error_text")->setText("Eine gültige PLZ besteht aus 4 Zahlen.");
    }else{
        window->findChild<QLabel*>("error_text")->setText("");
        //window->findChild<QPushButton*>("button")->setEnabled(true);
    }
}

void InputValidator::ueberpruefeOrt(QWidget *window){
    setOrt_erlaubt(window->findChild<QLineEdit*>("ort_input")->hasAcceptableInput());
    if(getOrt_erlaubt() == false){
        window->findChild<QLabel*>("error_text")->setText("Nur Eingabe von Buchstaben möglich.");
    }else{
        window->findChild<QLabel*>("error_text")->setText("");
        //window->findChild<QPushButton*>("button")->setEnabled(true);
    }
}

void InputValidator::ueberpruefePasswort(QWidget *window){
    setPasswort_erlaubt(window->findChild<QLineEdit*>("passwort_input")->hasAcceptableInput());
    if(getPasswort_erlaubt() == false){
        window->findChild<QLabel*>("error_text")->setText("Das ist kein gültiges Passwort.");
    }else{
        window->findChild<QLabel*>("error_text")->setText("");
        //window->findChild<QPushButton*>("button")->setEnabled(true);
    }
}

void InputValidator::ueberpruefe2Passwort(QWidget *window){
    setPasswort_erlaubt(window->findChild<QLineEdit*>("passwort2_input")->hasAcceptableInput());
    if(getPasswort_erlaubt() == false){
        window->findChild<QLabel*>("error_text")->setText("Das zweite Passwort ist kein gültiges Passwort.");
    }else{
        window->findChild<QLabel*>("error_text")->setText("");
        //window->findChild<QPushButton*>("button")->setEnabled(true);
    }
}
