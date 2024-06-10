#include "admindashboard.h"
#include "ui_admindashboard.h"

#include "dbaccess.h"

AdminDashboard::AdminDashboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminDashboard)
    , timer(new QTimer(this))
{

    if(currentEmployee->getAdmin() == false){ // double check if current Employeee is Admin
        qDebug() << "User tries to get into Admin-Page somehow";
        return;
    }

    dbZugriff->getAllEmployees(); //nur hier und nicht im admindashboard sonst wird vecotr zwei mal befüllt

    ui->setupUi(this);

    connect(timer, &QTimer::timeout, this, &AdminDashboard::updateGeneralData);
    timer->start(5000);  // Set the timer to trigger every 5 seconds

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

    this->updateEmployeeList();
    this->updateGeneralData();

}

void AdminDashboard::updateEmployeeList() {
    ui->employee_list->clear();

    for(int i = 0; i < dbZugriff->persons.size(); i++){
        QListWidgetItem *listitem = new QListWidgetItem();

        dbZugriff->mitarbeiter.push_back(new MitarbeiterView(this, i+1, dbZugriff->persons[i]));
        connect(dbZugriff->mitarbeiter.back(), &MitarbeiterView::editEmployee, this, &AdminDashboard::processEditMitarbeiter);

        listitem->setSizeHint(dbZugriff->mitarbeiter.back()->sizeHint());
        ui->employee_list->addItem(listitem);
        ui->employee_list->setItemWidget(listitem, dbZugriff->mitarbeiter.back());
    }
}

void AdminDashboard::updateGeneralData() {

    ui->employee_count_label->setText(QString::number(dbZugriff->persons.size()));

    dbZugriff->loadActiveEmployeeCount();
    ui->active_employee_count_label->setText(QString::number(dbZugriff->active_persons_count));


}

