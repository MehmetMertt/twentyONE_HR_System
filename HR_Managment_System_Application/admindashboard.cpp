#include "admindashboard.h"
#include "ui_admindashboard.h"

#include "mitarbeiterview.h"
#include "person.h"
#include "dbaccess.h"

AdminDashboard::AdminDashboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminDashboard)
{

    if(currentEmployee->getAdmin() == false){ // double check if current Employeee is Admin
        qDebug() << "User tries to get into Admin-Page somehow";
        return;
    }

    ui->setupUi(this);



    QListWidgetItem* listitem;
    MitarbeiterView* mitarbeiter;
    for(int i = 0; i < 1; i++) {
        listitem = new QListWidgetItem();
        mitarbeiter = new MitarbeiterView(this, currentEmployee);

        connect(mitarbeiter, &MitarbeiterView::editEmployee, this, &AdminDashboard::processEditMitarbeiter);

        listitem->setSizeHint(mitarbeiter->sizeHint());

        ui->employee_list->addItem(listitem);
        ui->employee_list->setItemWidget(listitem, mitarbeiter);


    }
}

AdminDashboard::~AdminDashboard()
{
    delete ui;
}

void AdminDashboard::on_new_employee_button_clicked()
{
    emit new_employee_clicked();
}

void AdminDashboard::processEditMitarbeiter(int id) {
    qDebug() << "dashboard edit " << id;
    emit edit_employee(id);
}

