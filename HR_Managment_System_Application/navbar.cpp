#include "navbar.h"
#include "ui_navbar.h"
#include <QFile>

Navbar::Navbar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Navbar)
{
    ui->setupUi(this);


    // Load the stylesheet from a file (recommended)
    QString stylesheetPath = ":sidebar/sidebar_stylesheet.qss"; // Assuming your stylesheet is in a resources file named "login.qss"
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
