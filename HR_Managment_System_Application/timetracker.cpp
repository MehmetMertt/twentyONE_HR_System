#include "timetracker.h"
#include "ui_timetracker.h"

Timetracker::Timetracker(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Timetracker)
{
    ui->setupUi(this);
}

Timetracker::~Timetracker()
{
    delete ui;
}
