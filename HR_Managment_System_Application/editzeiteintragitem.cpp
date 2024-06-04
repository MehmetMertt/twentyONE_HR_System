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

    connect(ui->startzeit, &QDateTimeEdit::dateTimeChanged, this, &EditZeiteintragItem::updateTimestamp);
    connect(ui->endzeit, &QDateTimeEdit::dateTimeChanged, this, &EditZeiteintragItem::updateTimestamp);

}

EditZeiteintragItem::~EditZeiteintragItem()
{
    delete ui;
}

void EditZeiteintragItem::initPage() {
    ui->startzeit->setDateTime(this->timestamp->data.first);
    ui->endzeit->setDateTime(this->timestamp->data.second);
}

QDateTime EditZeiteintragItem::getStartzeit() {
    return this->timestamp->data.first;
}

QDateTime EditZeiteintragItem::getEndzeit() {
    return this->timestamp->data.second;
}

QString EditZeiteintragItem::getNotiz() {
    return ui->notiz->text();
}

int EditZeiteintragItem::getID() {
    return this->id;
}

void EditZeiteintragItem::updateTimestamp() {
    this->timestamp->data.first = ui->startzeit->dateTime();
    this->timestamp->data.second = ui->endzeit->dateTime();
}
