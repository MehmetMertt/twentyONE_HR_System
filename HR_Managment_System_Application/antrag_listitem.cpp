#include "antrag_listitem.h"
#include "ui_antrag_listitem.h"

Antrag::Antrag(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Antrag)
{
    ui->setupUi(this);
}

Antrag::~Antrag()
{
    delete ui;
}

void Antrag::on_details_button_clicked()
{
    emit detailsClicked();
}

