#include "mitarbeiterview.h"
#include "ui_mitarbeiterview.h"

using namespace std;

MitarbeiterView::MitarbeiterView(QWidget *parent, Person* mitarbeiter)
    : QWidget(parent)
    , ui(new Ui::MitarbeiterView)
{
    ui->setupUi(this);

    this->mitarbeiter = mitarbeiter;

    initData();
}

MitarbeiterView::~MitarbeiterView()
{
    delete ui;
}

void MitarbeiterView::initData() {

    ui->id_label->setText(QString::number(this->mitarbeiter->getID()));

    QString name = this->mitarbeiter->getName() + " " + this->mitarbeiter->getSurname();
    ui->name_label->setText(name);

    ui->mail_label->setText(this->mitarbeiter->getMail());

    ui->phone_label->setText(this->mitarbeiter->getPhone());
}

void MitarbeiterView::on_button_edit_clicked()
{
    qDebug() << "emview edit";
    emit editEmployee(this->mitarbeiter->getID());
}

