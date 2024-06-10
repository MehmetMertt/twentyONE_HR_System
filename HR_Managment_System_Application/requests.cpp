#include "requests.h"
#include "ui_requests.h"

#include "dbaccess.h"

Requests::Requests(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Requests)
{
    ui->setupUi(this);
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
