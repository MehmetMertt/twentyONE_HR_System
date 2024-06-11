#include "dashboard.h"
#include "ui_dashboard.h"

#include <QFile>
#include <QDateTime>

Dashboard::Dashboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    updateGreeting();


    // Load the stylesheet from a file (recommended)
    QString stylesheetPath = ":/resourcen/styles/main.qss"; // Assuming your stylesheet is in a resources file named "login.qss"
    QFile stylesheetFile(stylesheetPath);
    if (stylesheetFile.open(QIODevice::ReadOnly)) {
        QString stylesheet = stylesheetFile.readAll();
        setStyleSheet(stylesheet);
        stylesheetFile.close();
    } else {
        // Handle error: stylesheet file not found
        qWarning() << "Failed to load stylesheet from" << stylesheetPath;
    }



/*
    dbZugriff->getActiveEmployees(); //nur hier und nicht im admindashboard sonst wird vecotr zwei mal befüllt
    int anzahlActives = dbZugriff->activepersons.size();
    QString activeanzahl = QString::number(anzahlActives);
    ui->Anzahl->setText("Aktiv: " + activeanzahl);
*/
}
void Dashboard::updateGreeting()
{
    QTime currentTime = QTime::currentTime();
    QString greeting;


    if (currentTime.hour() < 12) {
        greeting = "Guten Morgen";
    } else if (currentTime.hour() < 14) {
        greeting = "Guten Mittag";
    } else if (currentTime.hour() <= 18) {
        greeting = "Guten Nachmittag";
    }else {
        greeting = "Guten Abend";
    }

    ui->wieso->setText(greeting);


}



Dashboard::~Dashboard()
{
    delete ui;
}
