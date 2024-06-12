#include "editzeiteintragitem.h"
#include "ui_editzeiteintragitem.h"

EditZeiteintragItem::EditZeiteintragItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EditZeiteintragItem)
{
    ui->setupUi(this);
}

EditZeiteintragItem::EditZeiteintragItem(QWidget *parent, int id, Timestamp* timestamp)
    : QWidget(parent)
    , ui(new Ui::EditZeiteintragItem)
{
    ui->setupUi(this);
    //qDebug() << "start: " << timestamp.first.toString() << " ende: " << timestamp.second.toString();
    this->id = id;
    this->timestamp = timestamp;

    initPage();

    connect(ui->start, &QDateTimeEdit::dateTimeChanged, this, &EditZeiteintragItem::updateTimestamp);
    connect(ui->ende, &QDateTimeEdit::dateTimeChanged, this, &EditZeiteintragItem::updateTimestamp);
/*
    validator = new InputValidator(this);
    connect(ui->start, &QDateTimeEdit::dateTimeChanged, this, &EditZeiteintragItem::onStartzeitChanged);
    connect(ui->ende, &QDateTimeEdit::dateTimeChanged, this, &EditZeiteintragItem::onEndzeitChanged);
    connect(ui->notiz, &QTextEdit::textChanged, this, &EditZeiteintragItem::onNotizChanged);
*/
}

EditZeiteintragItem::~EditZeiteintragItem()
{
    delete ui;
}

void EditZeiteintragItem::initPage() {
    ui->start->setDateTime(this->timestamp->data.first);
    ui->ende->setDateTime(this->timestamp->data.second);
}

QDateTime EditZeiteintragItem::getStartzeit() {
    return this->timestamp->data.first;
}

QDateTime EditZeiteintragItem::getEndzeit() {
    return this->timestamp->data.second;
}

QString EditZeiteintragItem::getNotiz() {
    return ui->notiz->toPlainText();
}

int EditZeiteintragItem::getID() {
    return this->id;
}

void EditZeiteintragItem::updateTimestamp() {
    this->timestamp->data.first = ui->start->dateTime();
    this->timestamp->data.second = ui->ende->dateTime();
}
/*
void EditZeiteintragItem::compareDatum(){
    validator->ueberpruefeDatum(this);
    if(validator->getDatum_erlaubt() == false){
        ui->error_text->setText("Start Datum kann nicht nach End Datum liegen.");
    }else
        ui->error_text->setText("");
}

void EditZeiteintragItem::onStartzeitChanged(){
    this->compareDatum();
}
void EditZeiteintragItem::onEndzeitChanged(){
    this->compareDatum();
}

void EditZeiteintragItem::onNotizChanged(){
    QString text = ui->notiz->toPlainText();
    int pos = 0; // Dummy-Position für die Validierung
    QValidator::State state = validator->Titel_validator->validate(text, pos); //Regex von Titel wiederverwenden

    if(state != QValidator::Acceptable){
        ui->error_text->setText("Es wurden keine Notiz eingegeben.");
    }else{
        ui->error_text->setText("");
    }
}
*/
