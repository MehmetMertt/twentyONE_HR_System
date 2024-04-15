#include "navbar.h"
#include "ui_navbar.h"

Navbar::Navbar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Navbar)
{
    ui->setupUi(this);
}

Navbar::~Navbar()
{
    delete ui;
}
