#include "dashboard.h"
#include "ui_dashboard.h"

#include <QFile>

Dashboard::Dashboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);
   /*
    QString stylesheetPath = ":/resourcen/styles/timetracker.qss"; // Assuming your stylesheet is in a resources file named "login.qss"
    QFile stylesheetFile(stylesheetPath);
    if (stylesheetFile.open(QIODevice::ReadOnly)) {
        QString stylesheet = stylesheetFile.readAll();
        setStyleSheet(stylesheet);
        stylesheetFile.close();
    } else {
        // Handle error: stylesheet file not found
        qWarning() << "Failed to load stylesheet from" << stylesheetPath;
    }*/


    int anzahlEmployees = dbZugriff->persons.size();
    QString anzahl = QString::number(anzahlEmployees);
    ui->Anzahl->setText("Anzahl: " + anzahl);
/*
    dbZugriff->getActiveEmployees(); //nur hier und nicht im admindashboard sonst wird vecotr zwei mal befüllt
    int anzahlActives = dbZugriff->activepersons.size();
    QString activeanzahl = QString::number(anzahlActives);
    ui->Anzahl->setText("Aktiv: " + activeanzahl);
*/
}

Dashboard::~Dashboard()
{
    delete ui;
}
