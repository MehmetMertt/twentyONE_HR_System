#include "mainwindow.h"
#include "ui_mainwindow.h"
/*
#include <dbaccess.h>
#include <QFile>
#include <QPropertyAnimation>
#include <QtSql/QSqlDatabase>
#include <//qDebug>
*/

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //DONT DELETE
    //Only commented for development
    //Uncomment to test loading and login

    //currentEmployee = new person(1,"mehmet","m","we","m","we","m","we","d");

    main_loading_page = new MainLoading(this);
    connect(main_loading_page, &MainLoading::loadingFinished, this, &MainWindow::onLoadingFinished);

    main_loading_page->setGeometry(this->geometry());
    main_loading_page->show();
    main_loading_page->loadDB();


    ui->close_nav_button->hide();
    ui->open_nav_button->hide();

    //Delete after development
   // dbZugriff = new dbmanager();
    //login_finished();



    // Load the stylesheet from a file (recommended)
    QString stylesheetPath = ":/resourcen/styles/main_stylesheet.qss"; // Assuming your stylesheet is in a resources file named "login.qss"
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

void MainWindow::onLoadingFinished() {
    login_page = new Login(this);
    ui->main->addWidget(login_page);
    ui->main->setCurrentWidget(login_page);
    connect(login_page, &Login::login_success, this, &MainWindow::login_finished);

}

void MainWindow::login_finished()
{

    navbar = new Navbar(this);
    navbar_comp = new Navbar_compact(this);


    ui->close_nav_button->show();
    ui->sidebar->addWidget(navbar);
    ui->sidebar_comp->addWidget(navbar_comp);

    navbar_comp->hide();

    dashboard = new Dashboard(this);
    account_page = new Account(this);
    timetracker_page = new Timetracker(this);
    request_page = new Requests(this);
    settings_page = new Settings(this);
    editZeiteintrag_page = new EditZeiteintrag(this);
    antrag_detail_page = new AntragDetails(this);

    ui->main->addWidget(dashboard);
    ui->main->addWidget(account_page);
    ui->main->addWidget(timetracker_page);
    ui->main->addWidget(request_page);
    ui->main->addWidget(settings_page);
    ui->main->addWidget(editZeiteintrag_page);
    ui->main->addWidget(antrag_detail_page);
    ui->main->setCurrentWidget(dashboard);


    connect(navbar, &Navbar::account_clicked, this, &MainWindow::showAccount);
    connect(navbar_comp, &Navbar_compact::account_clicked, this, &MainWindow::showAccount);
    connect(navbar, &Navbar::dashboard_clicked, this, &MainWindow::showDashboard);
    connect(navbar_comp, &Navbar_compact::dashboard_clicked, this, &MainWindow::showDashboard);
    connect(navbar, &Navbar::timetracker_clicked, this, &MainWindow::showTimetracker);
    connect(navbar_comp, &Navbar_compact::timetracker_clicked, this, &MainWindow::showTimetracker);
    connect(navbar, &Navbar::request_clicked, this, &MainWindow::showRequests);
    connect(navbar_comp, &Navbar_compact::request_clicked, this, &MainWindow::showRequests);
    connect(navbar, &Navbar::settings_clicked, this, &MainWindow::showSettings);
    connect(navbar_comp, &Navbar_compact::settings_clicked, this, &MainWindow::showSettings);
    connect(navbar, &Navbar::logout_clicked, settings_page, &Settings::logout);
    connect(navbar_comp, &Navbar_compact::logout_clicked, settings_page, &Settings::logout);
    connect(settings_page, &Settings::logout_success, this, &MainWindow::processLogout);

    connect(timetracker_page, &Timetracker::openEditZeiteintrag, this, &MainWindow::openEditZeiteintragView);
    connect(timetracker_page, &Timetracker::startTimetracker, dashboard, &Dashboard::showStopTracker);
    connect(timetracker_page, &Timetracker::stopTimetracker, dashboard, &Dashboard::showStartTracker);

    connect(editZeiteintrag_page, &EditZeiteintrag::zeiteintrag_saved, this, &MainWindow::showTimetracker);
    connect(editZeiteintrag_page, &EditZeiteintrag::edit_cancel, this, &MainWindow::showTimetracker);

    connect(request_page, &Requests::showAntragDetailPage, this, &MainWindow::showAntragDetailPage);
    connect(antrag_detail_page, &AntragDetails::antrag_submit_success, this, &MainWindow::showRequests);
    connect(antrag_detail_page, &AntragDetails::antrag_finish_show_admin, this, &MainWindow::showAdminDashboard);
    connect(antrag_detail_page, &AntragDetails::antrag_finish_show_requests, this, &MainWindow::showRequests);

    connect(dashboard, &Dashboard::goZeitaufzeichnung, this, &MainWindow::startZeitaufzeichnungFromDashboard);
    connect(dashboard, &Dashboard::stopZeitaufzeichnung, this, &MainWindow::stopZeitaufzeichnungFromDashboard);
    connect(dashboard, &Dashboard::goZeitaufzeichnung, navbar, &Navbar::setTimetrackerActive);
    connect(dashboard, &Dashboard::stopZeitaufzeichnung, navbar, &Navbar::setTimetrackerActive);
    connect(dashboard, &Dashboard::goZeitaufzeichnung, navbar_comp, &Navbar_compact::setTimetrackerActive);
    connect(dashboard, &Dashboard::stopZeitaufzeichnung, navbar_comp, &Navbar_compact::setTimetrackerActive);


    if(currentEmployee->getAdmin() == 1){
        admin_dashboard = new AdminDashboard(this);
        account_adminview_page = new Account_adminview(this);
        signup_page = new Signup(this);
        ui->main->addWidget(admin_dashboard);
        ui->main->addWidget(account_adminview_page);
        ui->main->addWidget(signup_page);
        connect(navbar, &Navbar::admin_clicked, this, &MainWindow::showAdminDashboard);
        connect(navbar_comp, &Navbar_compact::admin_clicked, this, &MainWindow::showAdminDashboard);
        connect(admin_dashboard, &AdminDashboard::new_employee_clicked, this, &MainWindow::showSignup);
        connect(signup_page, &Signup::signup_success, this, &MainWindow::loadEmployeesThenShowAdminDashboard);
        connect(admin_dashboard, &AdminDashboard::edit_employee, this, &MainWindow::openEditEmployeeView);
        connect(admin_dashboard, &AdminDashboard::showAntragDetailPage, this, &MainWindow::showAntragDetailPage);
        connect(account_adminview_page, &Account_adminview::updateNavbarData, navbar, &Navbar::setUserData);
    }
}


MainWindow::~MainWindow()
{
    if (settings_page != nullptr) {
        //qDebug() << "1";
        delete settings_page;
    }
    if (request_page != nullptr) {
        //qDebug() << "2";
        delete request_page;
    }
    if (timetracker_page != nullptr) {
        //qDebug() << "3";
        delete timetracker_page;
    }
    if (account_page != nullptr) {
        //qDebug() << "4";
        delete account_page;
    }
    if (dashboard != nullptr) {
        //qDebug() << "5";
        delete dashboard;
    }
    if (admin_dashboard != nullptr) {
        //qDebug() << "6";
        delete admin_dashboard;
    }
    if (account_adminview_page != nullptr) {
        //qDebug() << "7";
        delete account_adminview_page;
    }
    if (signup_page != nullptr) {
        //qDebug() << "8";
        delete signup_page;
    }
    if (navbar != nullptr) {
        //qDebug() << "9";
        delete navbar;
    }
    if (navbar_comp != nullptr) {
        //qDebug() << "10";
        delete navbar_comp;
    }
    if (login_page != nullptr) {
        //qDebug() << "11";
        delete login_page;
    }
    if (main_loading_page != nullptr) {
        //qDebug() << "12";
        delete main_loading_page;
    }
    if (editZeiteintrag_page != nullptr) {
        //qDebug() << "13";
        delete editZeiteintrag_page;
    }


    delete ui;
}



void MainWindow::on_close_nav_button_clicked()
{
    // Create a property animation for the sidebar's width
    QPropertyAnimation *animationNavbar = new QPropertyAnimation(navbar, "geometry");
    animationNavbar->setDuration(150); // 100ms animation duration
    animationNavbar->setEasingCurve(QEasingCurve::InCubic);

    navbar_closed_geometry = QRect(ui->sidebar->geometry().x(), ui->sidebar->geometry().y(), 0, ui->sidebar->geometry().height());

    // Animate the width from the current value to 0 (hidden)
    animationNavbar->setStartValue(navbar->geometry());
    animationNavbar->setEndValue(navbar_closed_geometry);

    // Connect the animation's finished signal to show the open button
    connect(animationNavbar, &QPropertyAnimation::finished, [this]() {
        navbar->hide();
        //ui->sidebar->removeWidget(navbar);

        //ui->sidebar_comp->addWidget(navbar_comp);
        navbar_comp->setActiveItem(navbar->getActiveItem());
        navbar_comp->show();
        ui->close_nav_button->hide();
        ui->open_nav_button->show();

        QPropertyAnimation *animationNavComp = new QPropertyAnimation(navbar_comp, "geometry");
        animationNavComp->setDuration(150); // 100ms animation duration
        animationNavComp->setEasingCurve(QEasingCurve::InCubic);

        navbar_comp_geometry = QRect(ui->sidebar_comp->geometry().x(), ui->sidebar_comp->geometry().y(), 70, ui->sidebar_comp->geometry().height());

        // Animate the width from the current value to 0 (hidden)
        animationNavComp->setStartValue(navbar_comp->geometry());
        animationNavComp->setEndValue(navbar_comp_geometry);

        // Start the animation
        animationNavComp->start();
    });
    // Start the animation
    animationNavbar->start();



}


void MainWindow::on_open_nav_button_clicked()
{
    QPropertyAnimation *animationNavComp = new QPropertyAnimation(navbar_comp, "geometry");
    animationNavComp->setDuration(200); // 100ms animation duration
    animationNavComp->setEasingCurve(QEasingCurve::InCubic);

    navbar_comp_closed_geometry = QRect(ui->sidebar_comp->geometry().x(), ui->sidebar_comp->geometry().y(), 0, ui->sidebar_comp->geometry().height());

    // Animate the width from 0 (hidden) to the current sidebar width
    animationNavComp->setStartValue(navbar_comp->geometry());
    animationNavComp->setEndValue(navbar_comp_closed_geometry);

    // Connect the animation's finished signal to hide the open button
    connect(animationNavComp, &QPropertyAnimation::finished, [this]() {
        navbar_comp->hide();
        //ui->sidebar_comp->removeWidget(navbar_comp);

        //ui->sidebar->addWidget(navbar);
        navbar->setActiveItem(navbar_comp->getActiveItem());
        navbar->show();
        //navbar->setGeometry(navbar_closed_geometry);
        ui->open_nav_button->hide();
        ui->close_nav_button->show();


        // Create a property animation for the sidebar's width
        QPropertyAnimation *animationNavbar = new QPropertyAnimation(navbar, "geometry");
        animationNavbar->setDuration(200); // 100ms animation duration
        animationNavbar->setEasingCurve(QEasingCurve::InCubic);

        navbar_geometry = QRect(ui->sidebar->geometry().x(), ui->sidebar->geometry().y(), 180, ui->sidebar->geometry().height());

        // Animate the width from 0 (hidden) to the current sidebar width
        animationNavbar->setStartValue(navbar->geometry());
        animationNavbar->setEndValue(navbar_geometry);

        // Start the animation
        animationNavbar->start();
    });

    // Start the animation
    animationNavComp->start();

}

void MainWindow::showAccount() {
    ui->main->setCurrentWidget(account_page);
}

void MainWindow::showDashboard() {
    dashboard->loadData();
    ui->main->setCurrentWidget(dashboard);
}

void MainWindow::showTimetracker(Mode mode) {
    if(mode == LOAD_DATA)
        timetracker_page->loadData();
    ui->main->setCurrentWidget(timetracker_page);
}

void MainWindow::showRequests(Mode mode) {
    request_page->updateView(mode);
    ui->main->setCurrentWidget(request_page);
}

void MainWindow::showAntragDetailPage(Mode mode, Mode page, Antrag* antrag) {
    if(antrag != nullptr) {
        antrag_detail_page->setAntrag(antrag);
    } else {
        antrag_detail_page->setAntrag(new Antrag());
    }
    antrag_detail_page->setPreviousPage(page);
    antrag_detail_page->setupPage(mode);
    antrag_detail_page->updateView();
    //qDebug() << "set widget";
    ui->main->setCurrentWidget(antrag_detail_page);
}

void MainWindow::showSettings() {
    ui->main->setCurrentWidget(settings_page);
}

void MainWindow::showAdminDashboard() {
    admin_dashboard->updateView();
    ui->main->setCurrentWidget(admin_dashboard);
}

void MainWindow::loadEmployeesThenShowAdminDashboard() {

    dbZugriff->getAllEmployees();
    this->admin_dashboard->updateView();
    this->showAdminDashboard();

}

void MainWindow::showSignup() {
    ui->main->setCurrentWidget(signup_page);
}

void MainWindow::processLogout() {
    ui->close_nav_button->hide();
    ui->open_nav_button->hide();
    navbar->hide();
    navbar_comp->hide();
    ui->main->setCurrentWidget(login_page);

}

void MainWindow::openEditEmployeeView(int id) {
    account_adminview_page->initPage(id);
    ui->main->setCurrentWidget(account_adminview_page);
}

void MainWindow::openEditZeiteintragView(QList<Timestamp*> timestamps) {
    editZeiteintrag_page->initPage(timestamps);
    ui->main->setCurrentWidget(editZeiteintrag_page);
}

void MainWindow::startZeitaufzeichnungFromDashboard(){
    timetracker_page->on_button_start_clicked();
    ui->main->setCurrentWidget(timetracker_page);
}

void MainWindow::stopZeitaufzeichnungFromDashboard() {
    timetracker_page->on_button_stop_clicked();
}
