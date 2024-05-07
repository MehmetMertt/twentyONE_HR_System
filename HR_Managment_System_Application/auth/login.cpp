#include "login.h"
#include "ui_login.h"
#include <QFile>

#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QLineEdit>
#include <dbaccess.h>


Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->error_text->hide(); // Man kann nicht vom Anfang an (bzw vom Designer) ein Label auf hide setzen, daher mittels code im Constructer
//------------------------------------------------- INPUT VALIDIERUNG: ---------------------------------------------------
    QRegularExpression regExp_email("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9]+(\.[a-zA-Z]{2,6})$");
    QValidator *email_validator = new QRegularExpressionValidator(regExp_email, this);
    ui->email_input->setValidator(email_validator);

    QRegularExpression regExp_password("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[\\W]).{8,}$");
    QValidator *passwort_validator = new QRegularExpressionValidator(regExp_password, this);
    ui->passwort_input->setValidator(passwort_validator);
//------------------------------------------------------------------------------------------------------------------------

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
}

Login::~Login()
{
    delete ui;
    /*
    delete email_validator;
    delete passwort_validator;
    */
}


void Login::on_login_button_clicked()
{
    bool login = dbZugriff->login(ui->email_input->text(),ui->passwort_input->text());
    qDebug() << ui->email_input->text();
    qDebug() << ui->passwort_input->text();
    if(login){
        emit login_success();
    } else {
        ui->error_text->show();
    }

}

