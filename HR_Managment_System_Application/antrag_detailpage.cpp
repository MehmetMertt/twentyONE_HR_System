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

    dbZugriff->loadAbsenceReasons();
    for(int i = 0; i < dbZugriff->absence_reasons.size(); i++){
        QString reason = dbZugriff->absence_reasons.value(i+1);
        ui->antrag_type->addItem(reason);
    }



    ui->antrag_type->setCurrentIndex(0);

    validator = new InputValidator(this);
    ui->titel_field->setValidator(validator->Titel_validator);

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

    //qDebug() << "Setup details";

    switch (mode) {
    case CREATE_ANTRAG:
        clearInputs();
        ui->button_ablehnen->hide();
        ui->button_akzeptieren->hide();
        ui->button_speichern->hide();
        ui->button_senden->show();
        ui->button_loeschen->hide();
        ui->header->setText("Neuen Antrag erstellen");
        enableInputs();
        break;
    case ANTRAG_ADMIN:
        ui->button_senden->hide();
        ui->button_ablehnen->hide();
        ui->button_akzeptieren->hide();
        ui->button_speichern->hide();
        ui->button_loeschen->show();
        ui->header->setText("Antrag details");
        //qDebug() << "get Mitarbeiter" << antrag->getEmployeeId();
        this->person = dbZugriff->getMitarbeiterByID(this->antrag->getEmployeeId());

        ui->userdata->setText("Von: " + this->person->getGender() + " " + this->person->getSurname() + " (" + this->person->getMail() + ")");

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
        ui->button_loeschen->hide();
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
    ui->startzeit_edit->setEnabled(value);
    ui->endzeit_edit->setEnabled(value);
    ui->notiz->setEnabled(value);
}

void AntragDetails::disableInputs() {
    setInputsEnabled(false);
}

void AntragDetails::enableInputs() {
    setInputsEnabled(true);
}

void AntragDetails::updateView() {

    //qDebug() << "update view";

    ui->titel_field->setText(this->antrag->getTitel());
    ui->antrag_type->setCurrentText(this->antrag->getReason());
    ui->label_status->setText("Status: " + this->antrag->getStatus());
    ui->notiz->insertPlainText(this->antrag->getNotiz());
    ui->startzeit_edit->setDateTime(this->antrag->getStart());
    ui->endzeit_edit->setDateTime(this->antrag->getEnde());


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
    ui->startzeit_edit->setDateTime(QDateTime::currentDateTime());
    ui->endzeit_edit->setDateTime(QDateTime::currentDateTime());
}

void AntragDetails::on_button_senden_clicked()
{
    //VALIDATION EINBAUEN
    validator->ueberpruefeTitel(this);
    validator->ueberpruefeDatum(this);

    if(validator->getTitel_erlaubt() == false){
        ui->error_text->setText("Titel darf nicht leer sein.");
    }else if(validator->getDatum_erlaubt() == false){
        ui->error_text->setText("Start Datum kann nicht nach End Datum liegen.");
    }else{
        ui->error_text->setText("");

        Antrag* new_antrag = new Antrag(nullptr, -1, currentEmployee->getID(), ui->titel_field->text(), ui->startzeit_edit->dateTime(), ui->endzeit_edit->dateTime(), ui->antrag_type->currentText(), ui->notiz->toPlainText(), "Neu");

        bool send_success = dbZugriff->submitAbsence(new_antrag);

        if(send_success) {

            dbZugriff->currentEmployee_requests.push_back(new_antrag);

            emit antrag_submit_success(NOTHING);
        }
    }
}


void AntragDetails::on_button_abbrechen_clicked()
{
    clearInputs();
    this->emitFinishSignal(NOTHING);
}


void AntragDetails::on_button_ablehnen_clicked()
{
    int antragId = this->antrag->getId();
    bool success = dbZugriff->changeStatusOfRequest(antragId,3);
    if(success){
        //qDebug() << "Status wurde geändert!";
        this->emitFinishSignal(LOAD_DATA);
    } else {
        //qDebug() << "Status wurde nicht geändert!";
    }
}


void AntragDetails::on_button_akzeptieren_clicked()
{
    int antragId = this->antrag->getId();
    bool success = dbZugriff->changeStatusOfRequest(antragId,2);
    if(success){
        //qDebug() << "Status wurde geändert!";
        this->emitFinishSignal(LOAD_DATA);
    } else {
        //qDebug() << "Status wurde nicht geändert!";
    }
}

void AntragDetails::setPreviousPage(Mode mode) {
    this->previousPage = mode;
}

void AntragDetails::emitFinishSignal(Mode mode) {
    if(this->previousPage == ADMIN_DASHBOARD) {
        emit antrag_finish_show_admin();
    } else {
        emit antrag_finish_show_requests(mode);
    }
}


void AntragDetails::on_button_loeschen_clicked()
{
    bool success = dbZugriff->deleteRequest(this->antrag->getId());
    if(success){
        //qDebug() << "Request wurde gelöscht!";
        this->emitFinishSignal(LOAD_DATA);
    } else {
        //qDebug() << "Request wurde nicht gelöscht!";
    }
}

void AntragDetails::on_button_speichern_clicked()
{
    int antragId = this->antrag->getId();
    QString titel = ui->titel_field->text();
    QDateTime start = ui->startzeit_edit->dateTime();
    QDateTime ende = ui->endzeit_edit->dateTime();
    int reason = ui->antrag_type->currentIndex() + 1;
    QString note = ui->notiz->toPlainText();
    bool success = dbZugriff->editRequest(antragId,titel,start,ende,reason,note);
    if(success){
        //qDebug() << "Antrag gespeichert!";
        this->emitFinishSignal(LOAD_DATA);
    } else {
        //qDebug() << "Antrag wurde nicht gespeichert!";
    }
}

