#include "login.h"
#include "ui_login.h"
#include <QFile>

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

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
    ui->email_input->setValidator(validator->Email_validator);
    ui->passwort_input->setValidator(validator->Passwort_validator);
    connect(ui->email_input, &QLineEdit::textChanged, this, &Login::onEmailInputChanged);
    connect(ui->passwort_input, &QLineEdit::textChanged, this, &Login::onPasswordInputChanged);

}

Login::~Login()
{
    delete validator;
    delete ui;
}

void Login::onEmailInputChanged(){ validator->ueberpruefeEmail(this); }
void Login::onPasswordInputChanged(){ validator->ueberpruefePasswort(this); }

void Login::on_button_clicked(){

    if(validator->getEmail_erlaubt() == false && validator->getPasswort_erlaubt() == false){
        ui->error_text->setText("Es wurden keine Daten eingegeben.");
        //ui->button->setEnabled(false);
    }else if(validator->getEmail_erlaubt() == false){
        ui->error_text->setText("Überprüfen Sie die Eingabe für die Email-Adresse.");
        //ui->button->setEnabled(false);
    }else if(validator->getPasswort_erlaubt() == false){
        ui->error_text->setText("Überprüfen Sie die Eingabe für das Passwort.");
        //ui->button->setEnabled(false);
    }else{
        QString Email = ui->email_input->text();
        QString Passwort = ui->passwort_input->text();

        //<Datenbankbefehl zum Einfügen der Personendaten in die DB>
        //oder eine andere Funktion

        //FÜR DEBUGGING:
        qWarning() << "Email: " << Email << "Passwort: " << Passwort;
    }

}

