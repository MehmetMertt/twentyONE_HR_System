#include "zeiteintrag.h"
#include "ui_zeiteintrag.h"

Zeiteintrag::Zeiteintrag(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Zeiteintrag)
{
    ui->setupUi(this);
}

Zeiteintrag::Zeiteintrag(int id, QDateTime date, QDateTime start, QDateTime ende, int duration, QString comment, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Zeiteintrag)
{

    this->id = id;
    this->comment = comment;
    this->date = date;
    this->start = start;
    this->ende = ende;
    this->duration = duration;


    ui->setupUi(this);

    ui->label_date->setText(this->date.toLocalTime().toString("dd.MM.yyyy"));
    ui->label_time->setText(this->start.toLocalTime().toString("hh:mm") + " - " + this->ende.toLocalTime().toString("hh:mm"));
    ui->label_duration->setText(QString::number(duration) + " h");

    ui->label_comment->hide();

    if(comment != "") {
        ui->label_comment->setText(comment);
        ui->label_comment->show();
    }
}

Zeiteintrag::~Zeiteintrag()
{
    delete ui;
}
