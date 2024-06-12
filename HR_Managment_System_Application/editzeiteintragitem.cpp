#include "editzeiteintragitem.h"
#include "ui_editzeiteintragitem.h"

#include <QFile>

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
