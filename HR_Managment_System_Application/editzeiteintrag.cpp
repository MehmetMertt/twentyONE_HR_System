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
    QString stylesheetPath = ":/resourcen/styles/timetracker.qss"; // Assuming your stylesheet is in a resources file named "login.qss"
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
    delete ui;
}

void EditZeiteintrag::initPage(QList<Timestamp*> timestamps) {

    ui->listWidget->clear();

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
    for (auto& timestamp : this->timestampItems) {
        qDebug() << timestamp->getStartzeit().toString() << " - " << timestamp->getEndzeit().toString();

        bool success = dbZugriff->createZeiteintrag(timestamp->getStartzeit().toLocalTime(), timestamp->getEndzeit(), timestamp->getNotiz(), currentEmployee->getID());

        if(!success) {
            qDebug() << "Create Zeiteintrag " << timestamp->getID() << " failed";
        } else {
            emit zeiteintrag_saved();
        }
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

