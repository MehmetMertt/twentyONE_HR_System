#include "antrag_detailpage.h"
#include "ui_antrag_detailpage.h"
#include "dbaccess.h"
#include <QFile>

AntragDetails::AntragDetails(QWidget *parent, Antrag* antrag)
    : QWidget(parent)
    , ui(new Ui::AntragDetails)
{
    ui->setupUi(this);
    this->antrag = antrag;

    QList<QString> absence_reasons;
    QSqlQuery query;
    query.prepare("SELECT reason from ABSENCE_REASON");

    if(query.exec() && query.size() > 0){
        while(query.next()){
            QString reason = query.value(0).toString();
            absence_reasons.append(reason);
            ui->antrag_type->addItem(reason);
        }
    }else
        ui->antrag_type->addItems({"Urlaub", "Zeitausgleich"});

    ui->antrag_type->setCurrentIndex(0);

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

    qDebug() << "Setup details";

    switch (mode) {
    case CREATE_ANTRAG:
        clearInputs();
        ui->button_ablehnen->hide();
        ui->button_akzeptieren->hide();
        ui->button_speichern->hide();
        ui->button_senden->show();
        ui->header->setText("Neuen Antrag erstellen");
        enableInputs();
        break;
    case ANTRAG_ADMIN:
        ui->button_senden->hide();
        ui->button_ablehnen->hide();
        ui->button_akzeptieren->hide();
        ui->button_speichern->hide();

        ui->header->setText("Antrag details");

        enableInputs();
        if(this->antrag->getStatus() == "Neu") {
            ui->button_speichern->show();
            ui->button_ablehnen->show();
            ui->button_akzeptieren->show();
            ui->header->setText("Antrag beantworten");
        } else {
            disableInputs();
        }

        break;
    default:
        ui->button_ablehnen->hide();
        ui->button_akzeptieren->hide();
        ui->button_speichern->hide();
        ui->button_senden->hide();
        ui->header->setText("Antrag details");
        disableInputs();
        if(this->antrag->getStatus() == "Neu") {
            ui->button_speichern->show();
            enableInputs();
        }
        break;
    }

}

void AntragDetails::setInputsEnabled(bool value) {
    ui->titel_field->setEnabled(value);
    ui->antrag_type->setEnabled(value);
    ui->start->setEnabled(value);
    ui->ende->setEnabled(value);
    ui->notiz->setEnabled(value);
}

void AntragDetails::disableInputs() {
    setInputsEnabled(false);
}

void AntragDetails::enableInputs() {
    setInputsEnabled(true);
}

void AntragDetails::updateView() {

    qDebug() << "update view";

    ui->titel_field->setText(this->antrag->getTitel());
    ui->antrag_type->setCurrentText(this->antrag->getReason());
    ui->label_status->setText("Status: " + this->antrag->getStatus());
    ui->notiz->insertPlainText(this->antrag->getNotiz());
    ui->start->setDateTime(this->antrag->getStart());
    ui->ende->setDateTime(this->antrag->getEnde());

}

void AntragDetails::setAntrag(Antrag* antrag) {
    this->antrag = antrag;
    clearInputs();
}

void AntragDetails::clearInputs() {
    ui->titel_field->clear();
    ui->antrag_type->setCurrentIndex(0);
    ui->label_status->setText("Status: Neu");
    ui->notiz->clear();;
    ui->start->setDateTime(QDateTime::currentDateTime());
    ui->ende->setDateTime(QDateTime::currentDateTime());
}

void AntragDetails::on_button_senden_clicked()
{
    //VALIDATION EINBAUEN


    Antrag* new_antrag = new Antrag(nullptr, -1, currentEmployee->getID(), ui->titel_field->text(), ui->start->dateTime(), ui->ende->dateTime(), ui->antrag_type->currentText(), ui->notiz->toPlainText(), "Neu");

    bool send_success = dbZugriff->submitAbsence(new_antrag);

    if(send_success) {

        dbZugriff->currentEmployee_requests.push_back(new_antrag);

        emit antrag_submit_success(NOTHING);
    }

}

