#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <dbaccess.h>
#include <QFile>
#include <QPropertyAnimation>
#include <QtSql/QSqlDatabase>
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->open_nav_button->hide();
    ui->close_nav_button->hide();

    main_loading_page = new MainLoading(this);
    connect(main_loading_page, &MainLoading::loadingFinished, this, &MainWindow::onLoadingFinished);

    main_loading_page->setGeometry(this->geometry());
    main_loading_page->show();
    main_loading_page->loadDB();





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
    //signup_page = new Signup(this);
    //account_page = new Account(this);
    //account_adminview_page = new Account_adminview(this);
    //ui->main->addWidget(login_page);


    ui->main->addWidget(login_page);
    ui->main->setCurrentWidget(login_page);
    connect(login_page, &Login::login_success, this, &MainWindow::login_finished);

    /*ui->close_nav_button->show();
    ui->sidebar->addWidget(navbar);

    ui->sidebar_comp->addWidget(navbar_comp);

    navbar_comp->hide();*/
}

void MainWindow::login_finished()
{
    ui->main->removeWidget(login_page);
    login_page->hide();

    navbar = new Navbar(this);
    navbar_comp = new Navbar_compact(this);

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

    connect(navbar, &Navbar::login_out_clicked, this, &MainWindow::processLoginOut);
    connect(navbar_comp, &Navbar_compact::login_out_clicked, this, &MainWindow::processLoginOut);


    ui->close_nav_button->show();
    ui->sidebar->addWidget(navbar);

    ui->sidebar_comp->addWidget(navbar_comp);

    navbar_comp->hide();

    dashboard = new Dashboard(this);
    account_page = new Account(this);
    timetracker_page = new Timetracker(this);
    request_page = new Requests(this);
    settings_page = new Settings(this);
    ui->main->addWidget(dashboard);
    ui->main->addWidget(account_page);
    ui->main->addWidget(timetracker_page);
    ui->main->addWidget(request_page);
    ui->main->addWidget(settings_page);
    ui->main->setCurrentWidget(dashboard);

}


MainWindow::~MainWindow()
{

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

        navbar_comp_geometry = QRect(ui->sidebar_comp->geometry().x(), ui->sidebar_comp->geometry().y(), 72, ui->sidebar_comp->geometry().height());

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

        navbar_geometry = QRect(ui->sidebar->geometry().x(), ui->sidebar->geometry().y(), 200, ui->sidebar->geometry().height());

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
    ui->main->setCurrentWidget(dashboard);
}

void MainWindow::showTimetracker() {
    ui->main->setCurrentWidget(timetracker_page);
}

void MainWindow::showRequests() {
    ui->main->setCurrentWidget(request_page);
}

void MainWindow::showSettings() {
    ui->main->setCurrentWidget(settings_page);
}

void MainWindow::processLoginOut() {
}

