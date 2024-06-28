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

    //updateView();
    //updateView(LOAD_DATA);

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

/*
 * FALSCH.
 * Im Admin Dashboard müssen Anträge von allem mitarbeitern geladen werden
void AdminDashboard::updateView(Mode mode) {
    if(mode == LOAD_DATA)
        dbZugriff->loadRequestsByEmployee(currentEmployee->getID());

    ui->antrag_list->clear();
    this->insertRequests();
}*/

void AdminDashboard::updateView() {
    dbZugriff->loadAllRequests();

    this->updateEmployeeList();
    this->updateGeneralData();
    this->insertRequests();
}

void AdminDashboard::updateEmployeeList() {
    ui->employee_list->clear();
    dbZugriff->mitarbeiter.clear();

    for(int i = 0; i < dbZugriff->persons.size(); i++){
        QListWidgetItem *listitem = new QListWidgetItem();

        dbZugriff->mitarbeiter.push_back(new MitarbeiterView(this, i+1, dbZugriff->persons[i]));
        connect(dbZugriff->mitarbeiter.back(), &MitarbeiterView::editEmployee, this, &AdminDashboard::processEditMitarbeiter);

        listitem->setSizeHint(dbZugriff->mitarbeiter.back()->sizeHint());
        ui->employee_list->addItem(listitem);
        ui->employee_list->setItemWidget(listitem, dbZugriff->mitarbeiter.back());
    }
}


void AdminDashboard::processAntragDetailClicked(Antrag* antrag) {
    if(currentEmployee->getAdmin()) {
        emit showAntragDetailPage(ANTRAG_ADMIN, ADMIN_DASHBOARD, antrag);
        return;
    }

    emit showAntragDetailPage(ANTRAG_DETAILS, ADMIN_DASHBOARD, antrag);
}

void AdminDashboard::insertRequests() {

    ui->antrag_list->clear();

    QListWidgetItem* listitem;
    AntragListItem* antrag_item;

    // Sort the requests by status
    std::sort(dbZugriff->requests.begin(), dbZugriff->requests.end(), [](const auto& a, const auto& b) {
        static const std::map<QString, int> statusPriority = { {"Neu", 0}, {"Abgelehnt", 1}, {"Akzeptiert", 2} };
        return statusPriority.at(a->getStatus()) < statusPriority.at(b->getStatus());
    });

    for (auto& antrag : dbZugriff->requests) {
        listitem = new QListWidgetItem();
        antrag_item = new AntragListItem(this, antrag);

        listitem->setSizeHint(antrag_item->sizeHint());

        ui->antrag_list->addItem(listitem);
        ui->antrag_list->setItemWidget(listitem, antrag_item);

        connect(antrag_item, &AntragListItem::detailsClicked, this, &AdminDashboard::processAntragDetailClicked);
    }

}

void AdminDashboard::updateAntragList() {
    ui->antrag_list->clear();


}

void AdminDashboard::updateGeneralData() {

    ui->employee_count_label->setText(QString::number(dbZugriff->persons.size()));

    dbZugriff->loadActiveEmployeeCount();
    ui->active_employee_count_label->setText(QString::number(dbZugriff->active_persons_count));

    int counter = 0;
    for(auto& antrag: dbZugriff->requests){
        if(antrag->getStatus() == "Neu")
            counter++;
    }

    ui->unread_requests_count_label->setText(QString::number(counter));
}

