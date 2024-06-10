#include "requests.h"
#include "ui_requests.h"

#include "dbaccess.h"
#include <QListWidgetItem>
#include "antrag_listitem.h"

Requests::Requests(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Requests)
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

Requests::~Requests()
{
    delete ui;
}



void Requests::on_new_antrag_button_clicked()
{
    emit showAntragDetailPage(CREATE_ANTRAG);
}

void Requests::processAntragDetailClicked() {
    if(currentEmployee->getAdmin()) {
        emit showAntragDetailPage(ANTRAG_ADMIN);
        return;
    }

    emit showAntragDetailPage(ANTRAG_DETAILS);
}

void Requests::updateView() {
    dbZugriff->loadRequestsByEmployee(currentEmployee->getID());


    this->insertRequests();
}

void Requests::insertRequests() {

    QListWidgetItem* listitem;
    AntragListItem* antrag_item;

    for(auto& antrag: dbZugriff->currentEmployee_requests) {
        listitem = new QListWidgetItem();
        antrag_item = new AntragListItem(this, antrag);

        listitem->setSizeHint(antrag_item->sizeHint());

        if(antrag->getStatus() != "Neu") {
            ui->closed_requests->addItem(listitem);
            ui->closed_requests->setItemWidget(listitem, antrag_item);
        } else {
            ui->new_requests->addItem(listitem);
            ui->new_requests->setItemWidget(listitem, antrag_item);
        }

    }

}
