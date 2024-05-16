#include "account.h"
#include "ui_account.h"
#include <QFile>
#include <dbaccess.h>
Account::Account(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Account)
{
    ui->setupUi(this);
    ui->account_tel->setText(currentEmployee->getPhone());
    ui->account_name->setText(currentEmployee->getName() + " " + currentEmployee->getSurname());
    ui->account_email->setText(currentEmployee->getMail());
    QString street = currentEmployee->getStreet();
    QString housenumber = currentEmployee->getHousenumber();
    QString plz = currentEmployee->getPLZ();
    QString city = currentEmployee->getCity();
    ui->account_adresse->setText(street + " " + housenumber + " " + plz + " " + city);
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
    ui->passwort_input->setValidator(validator->Passwort_validator);
    ui->passwort2_input->setValidator(validator->Passwort_validator);
    connect(ui->passwort_input, &QLineEdit::textChanged, this, &Account::onPasswortInputChanged);
    connect(ui->passwort2_input, &QLineEdit::textChanged, this, &Account::onPasswort2InputChanged);
}

Account::~Account()
{
    delete validator;
    delete ui;
}

void Account::onPasswortInputChanged(){ validator->ueberpruefePasswort(this); }
void Account::onPasswort2InputChanged(){ validator->ueberpruefe2Passwort(this); }

void Account::on_button_clicked(){
    ui->success_text->clear();

    if(ui->passwort_input->text() == ""){
        ui->error_text->setText("Das Passwortfeld ist leer.");
        //ui->button->setEnabled(false);
    }else if(ui->passwort_input->text() != ui->passwort2_input->text()){
        ui->error_text->setText("Die eingegebenen Passwörter stimmen nicht überein.");
        //ui->button->setEnabled(false);
    }else{
        ui->error_text->setText("");
        //ui->button->setEnabled(true);

        QString passwort = ui->passwort_input->text();
        QString passwort2 = ui->passwort2_input->text();

        bool changePassword = dbZugriff->changePassword(currentEmployee->getID(), passwort);

        if(changePassword) {
            ui->error_text->hide();
            ui->success_text->setText("Passwort erfolgreich geändert");

        } else {
            ui->error_text->setText("Ein Fehler ist aufgetreten");
            ui->error_text->show();
        }

        ui->passwort_input->clear();
        ui->passwort2_input->clear();
        ui->error_text->clear();

        //FÜR DEBUGGING:
        qWarning() << "Passwort: " << passwort << "\nPasswort2: " << passwort2;
    }
}
