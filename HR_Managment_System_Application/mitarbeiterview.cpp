#include "mitarbeiterview.h"
#include "ui_mitarbeiterview.h"

#include <QFile>

using namespace std;

MitarbeiterView::MitarbeiterView(QWidget *parent, int id, Person* mitarbeiter)
    : QWidget(parent)
    , ui(new Ui::MitarbeiterView)
{
    ui->setupUi(this);

    this->id = id;
    this->mitarbeiter = mitarbeiter;

    initData();

    // Load the stylesheet from a file (recommended)
    QString stylesheetPath = ":/resourcen/styles/main.qss"; // Assuming your stylesheet is in a resources file named "login.qss"
    QFile stylesheetFile(stylesheetPath);
    if (stylesheetFile.open(QIODevice::ReadOnly)) {
        QString stylesheet = stylesheetFile.readAll();
        setStyleSheet(stylesheet);
        stylesheetFile.close();
    } else {
        // Handle error: stylesheet file not found
        qWarning() << "Failed to load stylesheet from" << stylesheetPath;
    }
}

MitarbeiterView::~MitarbeiterView()
{
    delete ui;
}

void MitarbeiterView::initData() {

    ui->id_label->setText(QString::number(this->id));

    QString name = this->mitarbeiter->getName() + " " + this->mitarbeiter->getSurname();
    ui->name_label->setText(name);

    ui->mail_label->setText(this->mitarbeiter->getMail());

    ui->phone_label->setText(this->mitarbeiter->getPhone());
}

void MitarbeiterView::on_button_edit_clicked()
{
    //qDebug() << "emview edit";
    emit editEmployee(this->id-1);
}

