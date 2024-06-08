#include "admindashboard.h"
#include "ui_admindashboard.h"

#include "dbaccess.h"

AdminDashboard::AdminDashboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminDashboard)
{

    if(currentEmployee->getAdmin() == false){ // double check if current Employeee is Admin
        qDebug() << "User tries to get into Admin-Page somehow";
        return;
    }

    dbZugriff->getAllEmployees(); //nur hier und nicht im admindashboard sonst wird vecotr zwei mal befüllt

    ui->setupUi(this);


/*
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
//*/

    updateView();

//*/
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

void AdminDashboard::updateView() {

    ui->employee_list->clear();

    for(int i = 0; i < dbZugriff->persons.size(); i++){
        QListWidgetItem *listitem = new QListWidgetItem();
        dbZugriff->mitarbeiter.push_back(new MitarbeiterView(this, dbZugriff->persons[i]));
        connect(dbZugriff->mitarbeiter.back(), &MitarbeiterView::editEmployee, this, &AdminDashboard::processEditMitarbeiter);
        listitem->setSizeHint(dbZugriff->mitarbeiter.back()->sizeHint());
        ui->employee_list->addItem(listitem);
        ui->employee_list->setItemWidget(listitem, dbZugriff->mitarbeiter.back());
    }

}

