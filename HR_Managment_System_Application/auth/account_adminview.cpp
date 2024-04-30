#include "Account_adminview.h"
#include "ui_account_adminview.h"
#include <QFile>

Account_adminview::Account_adminview(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Account_adminview)
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
}

Account_adminview::~Account_adminview()
{
    delete ui;
}
