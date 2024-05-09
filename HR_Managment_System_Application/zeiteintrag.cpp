#include "zeiteintrag.h"
#include "ui_zeiteintrag.h"

Zeiteintrag::Zeiteintrag(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Zeiteintrag)
{
    ui->setupUi(this);
}

Zeiteintrag::Zeiteintrag(int id, QDateTime date, QDateTime startzeit, QDateTime endzeit, int dauer, QString notiz, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Zeiteintrag)
{

    this->id = id;
    this->notiz = notiz;
    this->date = date;
    this->startzeit = startzeit;
    this->endzeit = endzeit;
    this->dauer = dauer;


    ui->setupUi(this);

    ui->label_date->setText(this->date.toLocalTime().toString("dd.MM.yyyy"));
    ui->label_time->setText(this->startzeit.toLocalTime().toString("hh:mm") + " - " + this->endzeit.toLocalTime().toString("hh:mm"));
    ui->label_duration->setText(QString::number(dauer) + " h");

    ui->label_comment->hide();

    if(notiz != "") {
        ui->label_comment->setText(notiz);
        ui->label_comment->show();
    }
}

Zeiteintrag::~Zeiteintrag()
{
    delete ui;
}

void Zeiteintrag::setStartzeit(QDateTime startzeit){
    this->startzeit = startzeit;
}
void Zeiteintrag::setEndzeit(QDateTime endzeit){
    this->endzeit = endzeit;
}
void Zeiteintrag::setNotiz(QString notiz){
    this->notiz=notiz;
}


QDateTime Zeiteintrag::getStartzeit(){
    return this->startzeit;
}

QDateTime Zeiteintrag::getEndzeit(){
    return this->endzeit;
}
QString Zeiteintrag::getNotiz(){
    return this->notiz;
}