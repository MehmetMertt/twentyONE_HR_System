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
}

Account::~Account()
{
    delete ui;
}
