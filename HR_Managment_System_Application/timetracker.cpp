#include "timetracker.h"
#include "qtimer.h"
#include "ui_timetracker.h"
#include "zeiteintrag.h"
#include "dbaccess.h"

#include <QFile>

Timetracker::Timetracker(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Timetracker)
{
    ui->setupUi(this);

    ui->button_pause->hide();
    ui->button_stop->hide();
    ui->button_weiter->hide();
    ui->timer_label->hide();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Timetracker::updateTimer);


    // Load the first stylesheet from a file
    QString stylesheetPath1 = ":/resourcen/styles/main.qss";
    QFile stylesheetFile1(stylesheetPath1);
    QString stylesheet1;
    if (stylesheetFile1.open(QIODevice::ReadOnly)) {
        stylesheet1 = stylesheetFile1.readAll();
        stylesheetFile1.close();
    } else {
        qWarning() << "Failed to load stylesheet from" << stylesheetPath1;
    }

    // Load the second stylesheet from a file
    QString stylesheetPath2 = ":/resourcen/styles/auth_stylesheet.qss";
    QFile stylesheetFile2(stylesheetPath2);
    QString stylesheet2;
    if (stylesheetFile2.open(QIODevice::ReadOnly)) {
        stylesheet2 = stylesheetFile2.readAll();
        stylesheetFile2.close();
    } else {
        qWarning() << "Failed to load stylesheet from" << stylesheetPath2;
    }

    // Combine the stylesheets
    QString combinedStylesheet = stylesheet1 + "\n" + stylesheet2;

    // Set the combined stylesheet
    setStyleSheet(combinedStylesheet);
}

void Timetracker::loadData() {
    this->deleteAllZeiteinträge();

    ui->listWidget->clear();


    this->loadTimeentries();
    this->loadDashboardData();

}

void Timetracker::loadTimeentries() {
    QList<Zeiteintrag*> zeiteintrag_list = dbZugriff->getArbeitszeiten(currentEmployee->getID());

    QListWidgetItem* listitem;
    for(auto& zeiteintrag: zeiteintrag_list) {
        listitem = new QListWidgetItem();

        listitem->setSizeHint(zeiteintrag->sizeHint());

        ui->listWidget->addItem(listitem);
        ui->listWidget->setItemWidget(listitem, zeiteintrag);

        this->listitems.insert(zeiteintrag, listitem);
        connect(zeiteintrag, &Zeiteintrag::editZeiteintrag, this, &Timetracker::resizeListItem);
        connect(zeiteintrag, &Zeiteintrag::zeiteintragSaved, this, &Timetracker::loadDashboardData);
        connect(zeiteintrag, &Zeiteintrag::zeiteintrag_removed, this, &Timetracker::removeZeiteintragLocal);
    }

    /*for(auto& item: this->listitems) {
        //qDebug() << item;
    }*/
}

void Timetracker::loadDashboardData() {

    double wochenstunden = dbZugriff->getArbeitsstundenSpecific(currentEmployee->getID());

    double wochenstunden_percent = (wochenstunden/general_wochenstunden)*100;
    if(wochenstunden_percent > 100.0) {
        wochenstunden_percent = 100;
    }

    if(wochenstunden > 38.5)
        wochenstunden = 38.5;
    ui->wochenstunden_aktuell->setText(QString::number(wochenstunden));
    ui->progress_wochenstunden->setValue(wochenstunden_percent);
    ui->progress_wochenstunden->update();

    //qDebug() << wochenstunden_percent;

    double ueberstunden = wochenstunden - general_wochenstunden;
    if(ueberstunden <= 0) {
        ueberstunden = 0;
    }
    ui->ueberstunden_aktuell->setText(QString::number(ueberstunden));

    QDate today = QDate::currentDate();
    float avg_arbeit = wochenstunden / today.dayOfWeek(); //gibt den Wochentag als int aus (wenn Mittwoch ist, ist die Zahl 3)
    QString avg_arbeit_str = QString::number(avg_arbeit, 'f', 1);
    ui->durchschnitt_stunden->setText(avg_arbeit_str);
}

Timetracker::~Timetracker()
{
    if(timer_running) {
        dbZugriff->removeActiveEmployee(currentEmployee->getID());
    }


    for(auto& timestamp: this->timestamps) {
        delete timestamp;
    }

    QMapIterator<Zeiteintrag*, QListWidgetItem*> i(listitems);
    while (i.hasNext()) {
        i.next();
        delete i.key();
        delete i.value();
    }
    listitems.clear();

    delete this->timer;

    delete ui;
}

void Timetracker::on_button_start_clicked()
{
    ui->button_start->hide();
    ui->button_weiter->hide();
    ui->button_pause->show();
    ui->button_stop->show();
    ui->timer_label->show();
    ui->timer_label->setText("00:00:00");

    timestamps.clear();

    timestamps.push_back(new Timestamp(this, QDateTime::currentDateTime(), QDateTime::currentDateTime().addDays(-1)));
    ////qDebug() << "Startzeit: " << QDateTime::currentDateTime().toString() << ", Endzeit: " << QDateTime::currentDateTime().addDays(-1).toString();
    timer->start(1000);
    timer_running = true;

    dbZugriff->addActiveEmployee(currentEmployee->getID());

    emit startTimetracker();
}


void Timetracker::on_button_pause_clicked()
{
    ui->button_pause->hide();
    ui->button_weiter->show();

    timestamps.last()->data.second = QDateTime::currentDateTime();
    timer->stop();
    timer_running = false;

}


void Timetracker::on_button_stop_clicked()
{
    ui->button_pause->hide();
    ui->button_weiter->hide();
    ui->button_stop->hide();
    ui->button_start->show();
    ui->timer_label->hide();

    if(!ui->button_weiter->isVisible()) {
        timestamps.last()->data.second = QDateTime::currentDateTime();
    }

    timer->stop();
    timer_running = false;
    elapsedTime = 0;

    dbZugriff->removeActiveEmployee(currentEmployee->getID());

    /*foreach(const auto &timestamp, timestamps) {
        //qDebug() << "Startzeit: " << timestamp->data.first.toString() << ", Endzeit: " << timestamp->data.second.toString();
    }*/

    emit stopTimetracker();
    emit openEditZeiteintrag(timestamps);
}


void Timetracker::on_button_weiter_clicked()
{
    ui->button_weiter->hide();
    ui->button_pause->show();

    timestamps.push_back(new Timestamp(this, QDateTime::currentDateTime(), QDateTime()));
    timer->start(1000);
    timer_running = true;
}

void Timetracker::updateTimer() {
    if(timer_running) {
        elapsedTime++;
    }

    QTime time(0, 0, 0);
    time = time.addSecs(elapsedTime);
    ui->timer_label->setText(time.toString("hh:mm:ss"));
}

void Timetracker::on_button_neu_clicked()
{
    emit openEditZeiteintrag({new Timestamp()});
}

void Timetracker::resizeListItem(Zeiteintrag* zeiteintrag) {

    QSize current_size = this->listitems.find(zeiteintrag).value()->sizeHint();
    QSize new_size(current_size.width(), zeiteintrag->sizeHint().height());
    this->listitems.find(zeiteintrag).value()->setSizeHint(new_size);
}

void Timetracker::removeZeiteintragLocal() {

    this->loadData();

}

void Timetracker::deleteAllZeiteinträge() {
    QMapIterator<Zeiteintrag*, QListWidgetItem*> i(listitems);
    while (i.hasNext()) {
        i.next();
        delete i.key();
        delete i.value();
    }
    this->listitems.clear();

    // At this point, the map should be empty
    //qDebug() << "All Zeiteinträge and list items have been deleted.";
}

