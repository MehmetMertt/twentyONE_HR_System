#include "antrag_detailpage.h"
#include "ui_antrag_detailpage.h"

#include <QFile>

AntragDetails::AntragDetails(QWidget *parent, Antrag* antrag)
    : QWidget(parent)
    , ui(new Ui::AntragDetails)
{
    ui->setupUi(this);
    this->antrag = antrag;

    // Load the first stylesheet from a file
    QString stylesheetPath1 = ":/resourcen/styles/main.qss";
    QFile stylesheetFile1(stylesheetPath1);
    QString stylesheet1;
    if (stylesheetFile1.open(QIODevice::ReadOnly)) {
        stylesheet1 = stylesheetFile1.readAll();
        stylesheetFile1.close();
    } else {
        qWarning() << "Failed to load stylesheet from" << stylesheetPath1;
    }

    // Load the second stylesheet from a file
    QString stylesheetPath2 = ":/resourcen/styles/auth_stylesheet.qss";
    QFile stylesheetFile2(stylesheetPath2);
    QString stylesheet2;
    if (stylesheetFile2.open(QIODevice::ReadOnly)) {
        stylesheet2 = stylesheetFile2.readAll();
        stylesheetFile2.close();
    } else {
        qWarning() << "Failed to load stylesheet from" << stylesheetPath2;
    }

    // Combine the stylesheets
    QString combinedStylesheet = stylesheet1 + "\n" + stylesheet2;

    // Set the combined stylesheet
    setStyleSheet(combinedStylesheet);
}

AntragDetails::~AntragDetails()
{
    delete ui;
}

void AntragDetails::setupPage(Mode mode) {

    switch (mode) {
    case CREATE_ANTRAG:
        ui->button_ablehnen->hide();
        ui->button_akzeptieren->hide();
        ui->button_speichern->hide();
        ui->button_senden->show();
        ui->header->setText("Neuen Antrag erstellen");
        break;
    case ANTRAG_ADMIN:
        ui->button_ablehnen->show();
        ui->button_akzeptieren->show();
        ui->button_speichern->hide();
        ui->button_senden->hide();

        ui->header->setText("Antrag details");

        if(this->antrag->getStatus() == "Neu") {
            ui->header->setText("Antrag beantworten");
        }

        break;
    default:
        ui->button_ablehnen->hide();
        ui->button_akzeptieren->hide();
        ui->button_speichern->show();
        ui->button_senden->hide();
        ui->header->setText("Antrag details");
        break;
    }

}

void AntragDetails::updateView() {

    ui->titel_field->setText(this->antrag->getType());
    ui->antrag_type->setCurrentText(this->antrag->getType());
    ui->label_status->setText("Status: " + this->antrag->getStatus());
    ui->notiz->insertPlainText(this->antrag->getNotiz());

}

void AntragDetails::setAntrag(Antrag* antrag) {
    this->antrag = antrag;
}
