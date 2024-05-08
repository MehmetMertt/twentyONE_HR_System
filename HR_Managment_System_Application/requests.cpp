#include "requests.h"
#include "ui_requests.h"

Requests::Requests(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Requests)
{
    ui->setupUi(this);
}

Requests::~Requests()
{
    delete ui;
}
