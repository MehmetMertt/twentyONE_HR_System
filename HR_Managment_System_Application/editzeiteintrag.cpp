#include "editzeiteintrag.h"
#include "ui_editzeiteintrag.h"

#include <QFile>

#include "dbaccess.h"

EditZeiteintrag::EditZeiteintrag(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EditZeiteintrag)
{
    ui->setupUi(this);

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

EditZeiteintrag::~EditZeiteintrag()
{

    for(auto& timestamp: this->timestampItems) {
        delete timestamp;
    }

    delete ui;
}

void EditZeiteintrag::initPage(QList<Timestamp*> timestamps) {

    ui->listWidget->clear();
    qDeleteAll(this->timestampItems);
    this->timestampItems.clear();

    QListWidgetItem* listitem;
    EditZeiteintragItem* zeiteintrag;

    int counter = 0;
    for (auto& timestamp : timestamps) {
        listitem = new QListWidgetItem();
        zeiteintrag = new EditZeiteintragItem(this, counter, timestamp);
        this->timestampItems.push_back(zeiteintrag);

        listitem->setSizeHint(zeiteintrag->sizeHint());

        ui->listWidget->addItem(listitem);
        ui->listWidget->setItemWidget(listitem, zeiteintrag);
        counter++;
    }
}



void EditZeiteintrag::on_save_clicked()
{
    bool datum_valid = false; bool notiz_valid = false;
    for(int i = 0; i < this->timestampItems.size(); i++){
        notiz_valid = this->timestampItems[i]->validator->getTitel_erlaubt();
        datum_valid = this->timestampItems[i]->validator->getDatum_erlaubt();
        qDebug() << "valid: " << (notiz_valid == true && datum_valid == true) << " Zeiteintrag: " << i;
        if(datum_valid == false || notiz_valid == false)
            break;
    }

    if(notiz_valid == false){
        qDebug() << "Notiz is wrong";
        //ui->error_text->setText("Notiz darf nicht leer sein.");
    }else if(datum_valid == false){
        qDebug() << "Datum is wrong";
        //ui->error_text->setText("Start Datum kann nicht nach End Datum liegen.");
    }else{
        //ui->error_text->setText("");
        bool success;
        for (auto& timestamp : this->timestampItems) {
            qDebug() << timestamp->getStartzeit().toString() << " - " << timestamp->getEndzeit().toString();

            success = dbZugriff->createZeiteintrag(timestamp->getStartzeit().toLocalTime(), timestamp->getEndzeit(), timestamp->getNotiz(), currentEmployee->getID());

            if(!success) {
                qDebug() << "Create Zeiteintrag " << timestamp->getID() << " failed";
                break;
            }
        }

        if(!success) {
            qDebug() << "Error saving Zeiteinträge";
            //UI updaten
            return;
        }

        qDeleteAll(this->timestampItems);
        this->timestampItems.clear();
        emit zeiteintrag_saved(LOAD_DATA);
    }
}


void EditZeiteintrag::on_new_eintrag_clicked()
{
    QListWidgetItem* listitem = new QListWidgetItem();
    EditZeiteintragItem* zeiteintrag = new EditZeiteintragItem(this, this->timestampItems.count(), new Timestamp());
    this->timestampItems.push_back(zeiteintrag);

    listitem->setSizeHint(zeiteintrag->sizeHint());

    ui->listWidget->addItem(listitem);
    ui->listWidget->setItemWidget(listitem, zeiteintrag);

}


void EditZeiteintrag::on_cancel_clicked()
{
    qDeleteAll(this->timestampItems);
    this->timestampItems.clear();

    emit edit_cancel(NOTHING);
}

