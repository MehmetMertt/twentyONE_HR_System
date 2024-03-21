#include "navbar_compact.h"
#include "ui_navbar_compact.h"

Navbar_compact::Navbar_compact(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Navbar_compact)
{
    ui->setupUi(this);
}

Navbar_compact::~Navbar_compact()
{
    delete ui;
}
