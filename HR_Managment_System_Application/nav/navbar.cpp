#include "navbar.h"
#include "ui_navbar.h"
#include <QFile>
#include <QIcon>
#include <QStyle>

Navbar::Navbar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Navbar)
{
    ui->setupUi(this);

    processLoginOutButton(1);
    setUserData();

    active_item = ui->dashboard;

    items.insert("user", ui->user);
    items.insert("dashboard", ui->dashboard);
    items.insert("timetracker", ui->timetracker);
    items.insert("requests", ui->request);
    items.insert("settings", ui->settings);
    items.insert("login_out", ui->login_out_button);


    // Load the stylesheet from a file (recommended)
    QString stylesheetPath = ":/resourcen/styles/sidebar_stylesheet.qss"; // Assuming your stylesheet is in a resources file named "login.qss"
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

Navbar::~Navbar()
{
    delete ui;
}

void Navbar::processLoginOutButton(int logged) {
    if(logged) {
        ui->login_out_button->setText("Logout");
        ui->login_out_button->setIcon(QIcon(":/resourcen/icons/logout.svg"));
    } else {
        ui->login_out_button->setText("Login");
        ui->login_out_button->setIcon(QIcon(":/resourcen/icons/login.svg"));
    }
}

void Navbar::setUserData() {
    ui->user->setText("Florian Mimmler");
}

void Navbar::on_user_clicked()
{
    removeActiveItem();
    active_item = ui->user;
    addActiveItem();
    emit account_clicked();
}


void Navbar::on_dashboard_clicked()
{
    removeActiveItem();
    active_item = ui->dashboard;
    addActiveItem();
    emit dashboard_clicked();
}

void Navbar::on_timetracker_clicked()
{
    removeActiveItem();
    active_item = ui->timetracker;
    addActiveItem();
    emit timetracker_clicked();
}

void Navbar::on_request_clicked()
{
    removeActiveItem();
    active_item = ui->request;
    addActiveItem();
    emit request_clicked();
}


void Navbar::on_settings_clicked()
{
    removeActiveItem();
    active_item = ui->settings;
    addActiveItem();
    emit settings_clicked();
}


void Navbar::on_login_out_button_clicked()
{
    removeActiveItem();
    active_item = ui->login_out_button;
    addActiveItem();
    emit login_out_clicked();
}

void Navbar::removeActiveItem() {
    active_item->setProperty("active_item", false);
    active_item->style()->unpolish(active_item);
    active_item->style()->polish(active_item);
}

void Navbar::addActiveItem() {
    active_item->setProperty("active_item", true);
    active_item->style()->unpolish(active_item);
    active_item->style()->polish(active_item);
}

void Navbar::setActiveItem(QString item) {
    removeActiveItem();
    active_item = items.value(item);
    addActiveItem();
}

QString Navbar::getActiveItem() {
    return items.key(active_item);
}








