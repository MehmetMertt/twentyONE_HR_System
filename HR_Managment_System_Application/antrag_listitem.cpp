#include "antrag_listitem.h"
#include "ui_antrag_listitem.h"

AntragListItem::AntragListItem(QWidget *parent, Antrag* antrag)
    : QWidget(parent)
    , ui(new Ui::AntragListItem)
{
    ui->setupUi(this);
    this->antrag = antrag;
    updateView();
}

AntragListItem::~AntragListItem()
{
    delete ui;
}

void AntragListItem::on_details_button_clicked()
{
    emit detailsClicked(this->antrag);
}

void AntragListItem::updateView() {
    ui->label_id->setText(QString::number(this->antrag->getId()));
    ui->label_titel->setText(this->antrag->getTitel());
    ui->label_status->setText(this->antrag->getStatus());
    ui->label_datum->setText(this->antrag->getStart().toString("dd.MM.yyyy hh:mm") + " - " + this->antrag->getEnde().toString("dd.MM.yyyy hh:mm"));
    ui->label_reason->setText(this->antrag->getReason());
}
