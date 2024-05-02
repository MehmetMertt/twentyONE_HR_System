#include "navbar.h"
#include "ui_navbar.h"
#include <QFile>
#include <QIcon>

Navbar::Navbar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Navbar)
{
    ui->setupUi(this);

    processLoginOutButton(1);
    setUserData();


    // Load the stylesheet from a file (recommended)
    QString stylesheetPath = ":/resourcen/styles/sidebar_stylesheet.qss"; // Assuming your stylesheet is in a resources file named "login.qss"
    QFile stylesheetFile(stylesheetPath);
    if (stylesheetFile.open(QIODevice::ReadOnly)) {
        QString stylesheet = stylesheetFile.readAll();
        setStyleSheet(stylesheet);
        stylesheetFile.close();
    } else {
        // Handle error: stylesheet file not found
        qWarning() << "Failed to load stylesheet from" << stylesheetPath;
    }
}

Navbar::~Navbar()
{
    delete ui;
}

void Navbar::processLoginOutButton(int logged) {
    if(logged) {
        ui->login_out_button->setText("Logout");
        ui->login_out_button->setIcon(QIcon(":/resourcen/icons/logout.svg"));
    } else {
        ui->login_out_button->setText("Login");
        ui->login_out_button->setIcon(QIcon(":/resourcen/icons/login.svg"));
    }
}

void Navbar::setUserData() {
    ui->username->setText("Florian Mimmler");
}
