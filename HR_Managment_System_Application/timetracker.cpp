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


    // Load the stylesheet from a file (recommended)
    QString stylesheetPath = ":/resourcen/styles/timetracker.qss"; // Assuming your stylesheet is in a resources file named "login.qss"
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

void Timetracker::loadData() {
    ui->listWidget->clear();

    QList<Zeiteintrag*> zeiteintrag_list = dbZugriff->getArbeitszeiten(currentEmployee->getID());

    QListWidgetItem* listitem;
    for(auto& zeiteintrag: zeiteintrag_list) {
        listitem = new QListWidgetItem();

        listitem->setSizeHint(zeiteintrag->sizeHint());

        ui->listWidget->addItem(listitem);
        ui->listWidget->setItemWidget(listitem, zeiteintrag);
    }
}

Timetracker::~Timetracker()
{
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
    //qDebug() << "Startzeit: " << QDateTime::currentDateTime().toString() << ", Endzeit: " << QDateTime::currentDateTime().addDays(-1).toString();
    timer->start(1000);
    timer_running = true;

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

    foreach(const auto &timestamp, timestamps) {
        qDebug() << "Startzeit: " << timestamp->data.first.toString() << ", Endzeit: " << timestamp->data.second.toString();
    }

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

