#include "account.h"
#include "ui_account.h"
#include <QFile>

Account::Account(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Account)
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


    if(ui->passwort_input->text() == ""){
        ui->error_text->setText("Das Passwortfeld ist leer.");
        //ui->button->setEnabled(false);
    }else if(ui->passwort_input->text() == ui->passwort2_input->text()){
        ui->error_text->setText("");
        //ui->button->setEnabled(true);

        QString Passwort = ui->passwort_input->text();
        QString Passwort2 = ui->passwort2_input->text();

        //Passwort in der DB aktualisieren

        //FÜR DEBUGGING:
        qWarning() << "Passwort: " << Passwort << "\nPasswort2: " << Passwort2;

    }else{
        ui->error_text->setText("Die eingegebenen Passwörter stimmen nicht überein.");
        //ui->button->setEnabled(false);
    }
}
