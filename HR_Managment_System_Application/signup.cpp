#include "signup.h"
#include "ui_signup.h"
#include <QFile>

Signup::Signup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Signup)
{
    ui->setupUi(this);
    ui->signup_button->setEnabled(false);
    ui->anrede_input->addItems({"Herr", "Frau", "Divers"});

//------------------------------------------------- INPUT VALIDIERUNG: ---------------------------------------------------
    QRegularExpression RegExp_name("[A-Za-zäöüßÄÖÜ]+");
    this->Vorname_validator = new QRegularExpressionValidator(RegExp_name, this);
    this->Nachname_validator = new QRegularExpressionValidator(RegExp_name, this);
    this->Ort_validator = new QRegularExpressionValidator(RegExp_name, this);
    ui->vorname_input->setValidator(this->Vorname_validator);
    ui->nachname_input->setValidator(this->Nachname_validator);
    ui->ort_input->setValidator(this->Ort_validator); //selbes Regex für Ort verwenden

    QRegularExpression RegExp_email("^[a-zA-Z0-9]+(\.[a-zA-Z0-9]+)?@[a-zA-Z0-9]+(\.[a-zA-Z]+)$");
    this->Email_validator = new QRegularExpressionValidator(RegExp_email, this);
    ui->email_input->setValidator(this->Email_validator);

    QRegularExpression RegExp_telefon("\\+43[0-9]{1,3}[0-9]{1,7}"); //"\\+[0-9]{1,4} [0-9]{1,3} [0-9]{1,7}"
    this->Telefon_validator = new QRegularExpressionValidator(RegExp_telefon, this);
    ui->tel_input->setValidator(this->Telefon_validator);

    QRegularExpression RegExp_plz("[0-9]{4}");
    this->Plz_validator = new QRegularExpressionValidator(RegExp_plz, this);
    ui->plz_input->setValidator(this->Plz_validator);

    QRegularExpression RegExp_passwort("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[\\W]).{8,}$");
    this->Passwort_validator = new QRegularExpressionValidator(RegExp_passwort, this);
    ui->passwort_input->setValidator(this->Passwort_validator);

    //die connects verbinden die Validierungsfunktionen (ueberprufeIrgendwas) an das QLineirgendwas
    connect(ui->vorname_input, &QLineEdit::textChanged, this, &Signup::ueberpruefeVorname);
    connect(ui->nachname_input, &QLineEdit::textChanged, this, &Signup::ueberpruefeNachname);
    connect(ui->email_input, &QLineEdit::textChanged, this, &Signup::ueberpruefeEmail);
    connect(ui->tel_input, &QLineEdit::textChanged, this, &Signup::ueberpruefeTelefon);
    connect(ui->plz_input, &QLineEdit::textChanged, this, &Signup::ueberpruefePlz);
    connect(ui->ort_input, &QLineEdit::textChanged, this, &Signup::ueberpruefeOrt);
    connect(ui->passwort_input, &QLineEdit::textChanged, this, &Signup::ueberpruefePasswort);
    //connect(ui->passwort_input, &QLineEdit::textChanged, this, &Signup::alleEingabenCheck);
    connect(ui->vorname_input, &QLineEdit::textChanged, this, &Signup::alleEingabenCheck);
    connect(ui->nachname_input, &QLineEdit::textChanged, this, &Signup::alleEingabenCheck);
    connect(ui->email_input, &QLineEdit::textChanged, this, &Signup::alleEingabenCheck);
    connect(ui->tel_input, &QLineEdit::textChanged, this, &Signup::alleEingabenCheck);
    connect(ui->plz_input, &QLineEdit::textChanged, this, &Signup::alleEingabenCheck);
    connect(ui->ort_input, &QLineEdit::textChanged, this, &Signup::alleEingabenCheck);
    connect(ui->passwort_input, &QLineEdit::textChanged, this, &Signup::alleEingabenCheck);
//------------------------------------------------------------------------------------------------------------------

    // Load the stylesheet from a file (recommended)
    QString stylesheetPath = ":styles/auth_stylesheet.qss"; // Assuming your stylesheet is in a resources file named "login.qss"
    QFile stylesheetFile(stylesheetPath);
    if (stylesheetFile.open(QIODevice::ReadOnly)) {
        QString stylesheet = stylesheetFile.readAll();
        setStyleSheet(stylesheet);
        stylesheetFile.close();
    } else {
        // Handle error: stylesheet file not found
        qWarning() << "Failed to load stylesheet from " << stylesheetPath;
    }

}

Signup::~Signup()
{
    delete this->Vorname_validator;
    delete this->Nachname_validator;
    delete this->Email_validator;
    delete this->Telefon_validator;
    delete this->Plz_validator;
    delete this->Ort_validator;
    delete this->Passwort_validator;
    delete ui;
}

void Signup::on_signup_button_clicked()
{   
    QString Titel = ui->titel_input->text();
    QString Anrede = ui->anrede_input->currentText();
    QString Vorname = ui->vorname_input->text();
    QString Nachname = ui->nachname_input->text();
    QString Ort = ui->ort_input->text();
    QString Email = ui->email_input->text();
    QString Telefon = ui->tel_input->text();
    QString Adresse = ui->adresse_input->text();
    QString Plz = ui->plz_input->text();
    QString Passwort = ui->passwort_input->text();

    //<Datenbankbefehl zum Einfügen der Personendaten in die DB>

    //FÜR DEBUGGING:
    qWarning() << "Titel: " << Titel << "\nAnrede: " << Anrede << "\nVorname: " << Vorname << "\nNachname: " << Nachname;
    qWarning() << "Email: " << Email << "\nTelefon: " << Telefon << "\nAdresse: " << Adresse << "\nPlz: " << Plz << "\nOrt: " << Ort;
    qWarning() << "Passwort: " << Passwort;

}

void Signup::ueberpruefeVorname(){
    Signup::setVorname_erlaubt(ui->vorname_input->hasAcceptableInput());
    if(Signup::getVorname_erlaubt() == false){
        ui->error_text->setText("Nur Eingabe von Buchstaben möglich.");
    }else{
        ui->error_text->setText("");
    }
}

void Signup::ueberpruefeNachname(){
    Signup::setNachname_erlaubt(ui->nachname_input->hasAcceptableInput());
    if(Signup::getNachname_erlaubt() == false){
        ui->error_text->setText("Nur Eingabe von Buchstaben möglich.");
    }else{
        ui->error_text->setText("");
    }
}

void Signup::ueberpruefeEmail(){
    Signup::setEmail_erlaubt(ui->email_input->hasAcceptableInput());
    if(Signup::getEmail_erlaubt() == false){
        ui->error_text->setText("Das ist keine gültige Email-Adresse.");
    }else{
        ui->error_text->setText("");
    }
}

void Signup::ueberpruefeTelefon(){
    Signup::setTelefon_erlaubt(ui->tel_input->hasAcceptableInput());
    if(Signup::getTelefon_erlaubt() == false){
        ui->error_text->setText("Die Telefonnummer muss mit +43 beginnen und nur die Eingabe von Zahlen ist erlaubt.");
    }else{
        ui->error_text->setText("");
    }
}

void Signup::ueberpruefePlz(){
    Signup::setPlz_erlaubt(ui->plz_input->hasAcceptableInput());
    if(Signup::getPlz_erlaubt() == false){
        ui->error_text->setText("Eine gültige PLZ besteht aus 4 Zahlen.");
    }else{
        ui->error_text->setText("");
    }
}

void Signup::ueberpruefeOrt(){
    Signup::setOrt_erlaubt(ui->ort_input->hasAcceptableInput());
    if(Signup::getOrt_erlaubt() == false){
        ui->error_text->setText("Nur Eingabe von Buchstaben möglich.");
    }else{
        ui->error_text->setText("");
    }
}

void Signup::ueberpruefePasswort(){
    Signup::setPasswort_erlaubt(ui->passwort_input->hasAcceptableInput());
    if(Signup::getPasswort_erlaubt() == false){
        ui->error_text->setText("Das Passwort muss mindestens einen Groß- und einen Kleinbuchstaben, eine Zahl und ein spezielles Zeichen beinhalten sowie mindestens 8 Zeichen lang sein.");
    }else{
        ui->error_text->setText("");
    }
}

void Signup::alleEingabenCheck(){
    if(Signup::getVorname_erlaubt() == true &&
        Signup::getNachname_erlaubt() == true &&
        Signup::getEmail_erlaubt() == true &&
        Signup::getTelefon_erlaubt() == true &&
        Signup::getPlz_erlaubt() == true &&
        Signup::getOrt_erlaubt() == true &&
        Signup::getPasswort_erlaubt() == true){
        ui->signup_button->setEnabled(true);
        //qWarning() << "alles passt.";
    }else{
        ui->signup_button->setEnabled(false);
        //qWarning() << "etwas passt nicht.";
        //qWarning() << ui->passwort_input->text();
    }
}
