#include "zeiteintrag.h"
#include "ui_zeiteintrag.h"

#include "dbaccess.h"

Zeiteintrag::Zeiteintrag(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Zeiteintrag)
{
    ui->setupUi(this);
}

Zeiteintrag::Zeiteintrag(int employeeId, QDateTime startzeit, QDateTime endzeit, double dauer, QString notiz, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Zeiteintrag)
{

    this->employeeId = employeeId;
    this->notiz = notiz;
    this->startzeit = startzeit;
    this->endzeit = endzeit;
    this->dauer = dauer;


    ui->setupUi(this);

    ui->edit_widget->hide();

    updateView();

    validator = new InputValidator(this);
    connect(ui->startzeit_edit, &QDateTimeEdit::dateTimeChanged, this, &Zeiteintrag::on_startzeit_edit_dateTimeChanged);
    connect(ui->endzeit_edit, &QDateTimeEdit::dateTimeChanged, this, &Zeiteintrag::on_endzeit_edit_dateTimeChanged);
    connect(ui->notiz_edit, &QTextEdit::textChanged, this, &Zeiteintrag::on_notiz_edit_textChanged);
}


Zeiteintrag::~Zeiteintrag()
{
    delete ui;
}

void Zeiteintrag::setStartzeit(QDateTime startzeit){
    this->startzeit = startzeit;
}
void Zeiteintrag::setEndzeit(QDateTime endzeit){
    this->endzeit = endzeit;
}
void Zeiteintrag::setNotiz(QString notiz){
    this->notiz=notiz;
}
void Zeiteintrag::setEmployeeId(int id){
    this->employeeId=id;
}
void Zeiteintrag::setTimentryId(int id){

    this->timeentryId=id;
}

QDateTime Zeiteintrag::getStartzeit(){
    return this->startzeit;
}

QDateTime Zeiteintrag::getEndzeit(){
    return this->endzeit;
}
QString Zeiteintrag::getNotiz(){
    return this->notiz;
}
int Zeiteintrag::getEmployeeId(){
    return this->employeeId;
}

int Zeiteintrag::getTimeentryId(){
    return this->timeentryId;
}

void Zeiteintrag::on_button_edit_clicked()
{
    ui->startzeit_edit->setDateTime(this->getStartzeit());
    ui->endzeit_edit->setDateTime(this->getEndzeit());
    ui->notiz_edit->setText(this->getNotiz());

    ui->edit_widget->show();
    ui->view_widget->hide();
    emit editZeiteintrag(this);
}


void Zeiteintrag::on_cancel_clicked()
{
    ui->edit_widget->hide();
    ui->view_widget->show();
    emit editZeiteintrag(this);
}


void Zeiteintrag::on_save_clicked()
{
    //Validation
    if(validator->getTitel_erlaubt() == false){
        qDebug() << "Titel nicht erlaubt";
        //ui->error_text->setText("Es wurden keine Notiz eingegeben.");
    }else if(validator->getDatum_erlaubt() == false){
        qDebug() << "Datum nicht erlaubt";
        //ui->error_text->setText("Start Datum kann nicht nach End Datum liegen.");
    }else{
        //ui->error_text->setText("Es wurden keine Notiz eingegeben.");
        bool edit_success = dbZugriff->editTimeentries(this->timeentryId, ui->startzeit_edit->dateTime(), ui->endzeit_edit->dateTime(), ui->notiz_edit->toPlainText());

        if(edit_success) {
            this->setStartzeit(ui->startzeit_edit->dateTime());
            this->setEndzeit(ui->endzeit_edit->dateTime());
            this->setNotiz(ui->notiz_edit->toPlainText());
            this->dauer = this->startzeit.secsTo(this->endzeit) / 3600.0;

            updateView();

            ui->edit_widget->hide();
            ui->view_widget->show();
            emit editZeiteintrag(this);
        } else {

        }
    }
}

void Zeiteintrag::updateView() {
    ui->label_date->setText(this->startzeit.toLocalTime().toString("dd.MM.yyyy"));
    ui->label_time->setText(this->startzeit.toLocalTime().toString("hh:mm") + " - " + this->endzeit.toLocalTime().toString("hh:mm"));
    ui->label_duration->setText(QString::number(dauer, 'f', 2) + " h");

    ui->notiz->hide();

    if(notiz != "") {
        ui->notiz->setText(notiz);
        ui->notiz->show();
    }
}

void Zeiteintrag::compareDatum(){
    validator->ueberpruefeDatum(this);
    /*
    if(validator->getDatum_erlaubt() == false){
        ui->error_text->setText("Start Datum kann nicht nach End Datum liegen.");
    }else
        ui->error_text->setText("");
    */
}

void Zeiteintrag::on_startzeit_edit_dateTimeChanged(){
    this->compareDatum();
}

void Zeiteintrag::on_endzeit_edit_dateTimeChanged(){
    this->compareDatum();
}

void Zeiteintrag::on_notiz_edit_textChanged(){
    validator->ueberpruefeNotiz(this);
}

void Zeiteintrag::on_remove_clicked(){
    int id = this->getTimeentryId();
    dbZugriff->deleteTimeentries(id);
}

