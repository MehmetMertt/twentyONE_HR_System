#include "inputvalidator.h"

InputValidator::InputValidator(QWidget *parent) : QObject(parent){

    QRegularExpression RegExp_name("[A-Za-zäöüßÄÖÜ]+");
    this->Vorname_validator = new QRegularExpressionValidator(RegExp_name, this);
    this->Nachname_validator = new QRegularExpressionValidator(RegExp_name, this);
    this->Ort_validator = new QRegularExpressionValidator(RegExp_name, this);

    //QRegularExpression RegExp_email("^[a-zA-Z0-9]+(\.[a-zA-Z0-9]+)?@[a-zA-Z0-9]+(\.[a-zA-Z]+)$");
    QRegularExpression RegExp_email("^[a-zA-Z0-9]+([.-][a-zA-Z0-9]+)*@[a-zA-Z]+(-[a-zA-Z]+)?\\.[a-zA-Z]{2,}$");
    this->Email_validator = new QRegularExpressionValidator(RegExp_email, this);

    QRegularExpression RegExp_telefon("\\+43[0-9]{1,3}[0-9]{1,8}");
    this->Telefon_validator = new QRegularExpressionValidator(RegExp_telefon, this);

    //QRegularExpression RegExp_adresse("^[A-Za-zäöüßÄÖÜ]+\\s?[0-9]+(/\\d+)?$");
    QRegularExpression RegExp_adresse("^[A-Za-zäöüßÄÖÜ]+(\\s[A-Za-zäöüßÄÖÜ]+)?\\s?[0-9]+(/\\d+)?$");
    this->Adresse_validator = new QRegularExpressionValidator(RegExp_adresse, this);

    QRegularExpression RegExp_plz("[0-9]{4}");
    this->Plz_validator = new QRegularExpressionValidator(RegExp_plz, this);

    QRegularExpression RegExp_passwort("^(?=.*[a-zäöüß])(?=.*[A-ZÄÖÜ])(?=.*\\d)(?=.*[\\W]).{8,}$");
    this->Passwort_validator = new QRegularExpressionValidator(RegExp_passwort, this);

    QRegularExpression RegExp_titel("[\\sA-Za-zäöüßÄÖÜ0-9!?§$%&/#~()-<>+*-/.:,;]+");
    this->Titel_validator = new QRegularExpressionValidator(RegExp_titel, this);

    this->Vorname_erlaubt = false;
    this->Nachname_erlaubt = false;
    this->Email_erlaubt = false;
    this->Telefon_erlaubt = false;
    this->Adresse_erlaubt = false;
    this->Plz_erlaubt = false;
    this->Ort_erlaubt = false;
    this->Passwort_erlaubt = false;
    this->Datum_erlaubt = false;
    this->Titel_erlaubt = false;
}

void InputValidator::ueberpruefeVorname(QWidget *window){
    setVorname_erlaubt(window->findChild<QLineEdit*>("vorname_input")->hasAcceptableInput());
    if(getVorname_erlaubt() == false){
        window->findChild<QLabel*>("error_text")->setText("Nur Eingabe von Buchstaben möglich.");
    }else{
        window->findChild<QLabel*>("error_text")->setText("");
    }
}

void InputValidator::ueberpruefeNachname(QWidget *window){
    setNachname_erlaubt(window->findChild<QLineEdit*>("nachname_input")->hasAcceptableInput());
    if(getNachname_erlaubt() == false){
        window->findChild<QLabel*>("error_text")->setText("Nur Eingabe von Buchstaben möglich.");
    }else{
        window->findChild<QLabel*>("error_text")->setText("");
    }
}

void InputValidator::ueberpruefeEmail(QWidget *window){
    setEmail_erlaubt(window->findChild<QLineEdit*>("email_input")->hasAcceptableInput());
    if(getEmail_erlaubt() == false) {
        window->findChild<QLabel*>("error_text")->setText("Das ist keine gültige Email-Adresse.");
    }else{
        window->findChild<QLabel*>("error_text")->setText("");
    }
}

void InputValidator::ueberpruefeTelefon(QWidget *window){
    setTelefon_erlaubt(window->findChild<QLineEdit*>("tel_input")->hasAcceptableInput());
    if(getTelefon_erlaubt() == false){
        window->findChild<QLabel*>("error_text")->setText("Die Telefonnummer muss mit +43 beginnen und nur die Eingabe von Zahlen ist erlaubt.");
    }else{
        window->findChild<QLabel*>("error_text")->setText("");
    }
}

void InputValidator::ueberpruefeAdresse(QWidget *window){
    setAdresse_erlaubt(window->findChild<QLineEdit*>("adresse_input")->hasAcceptableInput());
    if(getAdresse_erlaubt() == false){
        window->findChild<QLabel*>("error_text")->setText("Eine gültige Adresse besteht aus Buchstaben, Zahlen, Beichstrichen und Punkten.");
    }else{
        window->findChild<QLabel*>("error_text")->setText("");
    }
}

void InputValidator::ueberpruefePlz(QWidget *window){
    setPlz_erlaubt(window->findChild<QLineEdit*>("plz_input")->hasAcceptableInput());
    if(getPlz_erlaubt() == false){
        window->findChild<QLabel*>("error_text")->setText("Eine gültige PLZ besteht aus 4 Zahlen.");
    }else{
        window->findChild<QLabel*>("error_text")->setText("");
    }
}

void InputValidator::ueberpruefeOrt(QWidget *window){
    setOrt_erlaubt(window->findChild<QLineEdit*>("ort_input")->hasAcceptableInput());
    if(getOrt_erlaubt() == false){
        window->findChild<QLabel*>("error_text")->setText("Nur Eingabe von Buchstaben möglich.");
    }else{
        window->findChild<QLabel*>("error_text")->setText("");
    }
}

void InputValidator::ueberpruefePasswort(QWidget *window){
    setPasswort_erlaubt(window->findChild<QLineEdit*>("passwort_input")->hasAcceptableInput());
    if(getPasswort_erlaubt() == false){ //größter Pfusch dieser setText also wenn jmd was besser einfällt bitte umsetzen :)
        window->findChild<QLabel*>("error_text")->setText("Ein gültiges Passwort muss mindestens \n8 Zeichen lang sein und aus mindestens \n1 Großbuchstaben, 1 Kleinbuchstaben, 1 Zahl \nund 1 speziellen Zeichen bestehen.");
    }else{
        window->findChild<QLabel*>("error_text")->setText("");
    }
}

void InputValidator::ueberpruefe2Passwort(QWidget *window){
    setPasswort_erlaubt(window->findChild<QLineEdit*>("passwort2_input")->hasAcceptableInput());
    if(getPasswort_erlaubt() == false){
        window->findChild<QLabel*>("error_text")->setText("Das zweite Passwort ist kein gültiges Passwort.");
    }else{
        window->findChild<QLabel*>("error_text")->setText("");
    }
}

void InputValidator::ueberpruefeDatum(QWidget *window){

    QDateTimeEdit *start = window->findChild<QDateTimeEdit*>("startzeit_edit");
    QDateTimeEdit *ende = window->findChild<QDateTimeEdit*>("endzeit_edit");

    QDateTime start_zeit = start->dateTime();
    QDateTime ende_zeit = ende->dateTime();

    this->setDatum_erlaubt(start_zeit < ende_zeit);
}

void InputValidator::ueberpruefeTitel(QWidget *window){
    setTitel_erlaubt(window->findChild<QLineEdit*>("titel_field")->hasAcceptableInput());
}

void InputValidator::ueberpruefeNotiz(QWidget *window){
    QTextEdit *notizEdit = window->findChild<QTextEdit*>("notiz_edit");
    if(notizEdit){
        QString notizText = notizEdit->toPlainText();
        QLineEdit tempLineEdit;
        tempLineEdit.setValidator(this->Titel_validator);
        tempLineEdit.setText(notizText);

        setTitel_erlaubt(tempLineEdit.hasAcceptableInput());
    }
}


