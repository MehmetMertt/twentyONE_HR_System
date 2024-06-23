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

    this->loadData();

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

void Dashboard::loadData(){
    float wochenstunden = dbZugriff->getArbeitsstundenSpecific(currentEmployee->getID());
    if(wochenstunden > 38.5)
        wochenstunden = 38.5;
    ui->wochenstunden_aktuell->setText(QString::number(wochenstunden));

    float wochenstunden_percent = (wochenstunden/general_wochenstunden) * 100;
    if(wochenstunden_percent > 100.0)
        wochenstunden_percent = 100;

    ui->progress_wochenstunden->setValue(wochenstunden_percent);
    ui->progress_wochenstunden->update();

    int hours = dbZugriff->getAcceptedAbsences(currentEmployee->getID());
    int days = hours / 24.0;
    float days_left = 25.0 - days;
    if(days_left < 0)
        days_left = 0;

    float days_left_percent = (days_left / 25.0) * 100;
    ui->urlaub_progressBar->setValue(days_left_percent);
    ui->verbl_urlaub->setText(QString::number(static_cast<int>(days_left)));

    float ueberstunden = dbZugriff->getArbeitsstundenFromThisYear(currentEmployee->getID());
    ueberstunden -= days;

    if(ueberstunden < 0)
        ueberstunden = 0;

    ueberstunden = ueberstunden - 38.5;
    ui->ueberstunden_label->setText(QString::number(ueberstunden));
}

void Dashboard::on_pushButton_clicked(){
    //Zeitaufzeichnung starten und Zeitaufzeichnungsfenster als nächstes Widget setzen
    emit this->goZeitaufzeichnung();
}

