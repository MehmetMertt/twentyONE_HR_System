#include "antrag_detailpage.h"
#include "ui_antrag_detailpage.h"

CreateAntrag::CreateAntrag(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CreateAntrag)
{
    ui->setupUi(this);
}

CreateAntrag::~CreateAntrag()
{
    delete ui;
}
