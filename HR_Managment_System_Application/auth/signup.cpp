#include "signup.h"
#include "ui_signup.h"
#include <QFile>
#include "dbaccess.h"

Signup::Signup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Signup)
{
    ui->setupUi(this);
    ui->anrede_input->addItems({"Herr", "Frau", "Divers"});

    // Load the stylesheet from a file (recommended)
    QString stylesheetPath = ":/resourcen/styles/auth_stylesheet.qss"; // Assuming your stylesheet is in a resources file named "login.qss"
    QFile stylesheetFile(stylesheetPath);
    if (stylesheetFile.open(QIODevice::ReadOnly)) {
        QString stylesheet = stylesheetFile.readAll();
        setStyleSheet(stylesheet);
        stylesheetFile.close();
    } else {
        // Handle error: stylesheet file not found
        qWarning() << "Failed to load stylesheet from " << stylesheetPath;
    }

    validator = new InputValidator(this);
    ui->vorname_input->setValidator(validator->Vorname_validator);
    ui->nachname_input->setValidator(validator->Nachname_validator);
    ui->ort_input->setValidator(validator->Ort_validator); //selbes Regex für Ort verwenden
    ui->email_input->setValidator(validator->Email_validator);
    ui->tel_input->setValidator(validator->Telefon_validator);
    ui->adresse_input->setValidator(validator->Adresse_validator);
    ui->plz_input->setValidator(validator->Plz_validator);
    ui->passwort_input->setValidator(validator->Passwort_validator);

    //die connects verbinden die Validierungsfunktionen (ueberprufeIrgendwas) an die Inputfelder
    connect(ui->vorname_input, &QLineEdit::textChanged, this, &Signup::onVornameInputChanged);
    connect(ui->nachname_input, &QLineEdit::textChanged, this, &Signup::onNachnameInputChanged);
    connect(ui->email_input, &QLineEdit::textChanged, this, &Signup::onEmailInputChanged);
    connect(ui->tel_input, &QLineEdit::textChanged, this, &Signup::onTelefonInputChanged);
    connect(ui->adresse_input, &QLineEdit::textChanged, this, &Signup::onAdresseInputChanged);
    connect(ui->plz_input, &QLineEdit::textChanged, this, &Signup::onPlzInputChanged);
    connect(ui->ort_input, &QLineEdit::textChanged, this, &Signup::onOrtInputChanged);
    connect(ui->passwort_input, &QLineEdit::textChanged, this, &Signup::onPasswordInputChanged);

}

Signup::~Signup()
{
    delete validator;
    delete ui;
}

void Signup::onVornameInputChanged(){ validator->ueberpruefeVorname(this); }
void Signup::onNachnameInputChanged(){ validator->ueberpruefeNachname(this); }
void Signup::onEmailInputChanged(){ validator->ueberpruefeEmail(this); }
void Signup::onTelefonInputChanged(){ validator->ueberpruefeTelefon(this); }
void Signup::onAdresseInputChanged(){ validator->ueberpruefeAdresse(this); }
void Signup::onPlzInputChanged(){ validator->ueberpruefePlz(this); }
void Signup::onOrtInputChanged(){ validator->ueberpruefeOrt(this); }
void Signup::onPasswordInputChanged(){ validator->ueberpruefePasswort(this); }


void Signup::on_button_clicked()
{
    if(validator->getVorname_erlaubt() == false && validator->getNachname_erlaubt() == false && validator->getEmail_erlaubt() == false &&
       validator->getTelefon_erlaubt() == false && validator->getAdresse_erlaubt() == false && validator->getPlz_erlaubt() == false &&
       validator->getOrt_erlaubt() == false && validator->getPasswort_erlaubt() == false){
        ui->error_text->setText("Es wurden keine Daten eingegeben.");
        //ui->button->setEnabled(false);
    }else if(validator->getVorname_erlaubt() == false){
        ui->error_text->setText("Überprüfen Sie die Eingabe für den Vornamen.");
        //ui->button->setEnabled(false);
    }else if(validator->getNachname_erlaubt() == false){
        ui->error_text->setText("Überprüfen Sie die Eingabe für den Nachnamen.");
        //ui->button->setEnabled(false);
    }else if(validator->getEmail_erlaubt() == false){
        ui->error_text->setText("Überprüfen Sie die Eingabe für die Email-Adresse.");
        //ui->button->setEnabled(false);
    }else if(validator->getTelefon_erlaubt() == false){
        ui->error_text->setText("Überprüfen Sie die Eingabe für die Telefonnummer.");
        //ui->button->setEnabled(false);
    }else if(validator->getAdresse_erlaubt() == false){
        ui->error_text->setText("Überprüfen Sie die Eingabe für die Adresse.");
        //ui->button->setEnabled(false);
    }else if(validator->getPlz_erlaubt() == false){
        ui->error_text->setText("Überprüfen Sie die Eingabe für die Postleitzahl.");
        //ui->button->setEnabled(false);
    }else if(validator->getOrt_erlaubt() == false){
        ui->error_text->setText("Überprüfen Sie die Eingabe für den Ort.");
        //ui->button->setEnabled(false);
    }else if(validator->getPasswort_erlaubt() == false){
        ui->error_text->setText("Überprüfen Sie die Eingabe für das Passwort.");
        //ui->button->setEnabled(false);
    }else{
        QString Vorname = ui->vorname_input->text();
        QString Nachname = ui->nachname_input->text();
        QString Email = ui->email_input->text();
        QString Telefon = ui->tel_input->text();
        QString Adresse = ui->adresse_input->text();
        int Plz = ui->plz_input->text().toInt();
        QString Ort = ui->ort_input->text();
        QString Passwort = ui->passwort_input->text();
        QString title = ui->titel_input->text();

        //<Datenbankbefehl zum Einfügen der Personendaten in die DB>
        //zuerst in ADRESS einfügen und dann EMPLOYEE, weil so solls angeblich funktionieren, funktioniert aber nicht
        bool signup = dbZugriff->addMitarbeiterAdresse(Plz, Ort, Adresse);
        signup = dbZugriff->addMitarbeiter(Vorname, Nachname, Email, Telefon, Passwort);
        //oder eine andere Funktion
        //bool signup = dbZugriff->addMitarbeiter(Vorname, Nachname, Email, Telefon, Passwort,Adresse,Plz,Ort,title);

        if(signup == true) {
            ui->error_text->setText("");
            ui->error_text->hide();

            ui->vorname_input->clear();
            ui->nachname_input->clear();
            ui->email_input->clear();
            ui->tel_input->clear();
            ui->adresse_input->clear();
            ui->plz_input->clear();
            ui->ort_input->clear();
            ui->passwort_input->clear();

            emit signup_success();

        } else {
            ui->error_text->setText("Ein Fehler ist aufgetreten");
            ui->error_text->show();
        }
    }
}
