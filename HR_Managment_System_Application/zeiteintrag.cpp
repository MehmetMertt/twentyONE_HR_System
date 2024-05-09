#include "zeiteintrag.h"
#include "ui_zeiteintrag.h"

Zeiteintrag::Zeiteintrag(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Zeiteintrag)
{
    ui->setupUi(this);
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
