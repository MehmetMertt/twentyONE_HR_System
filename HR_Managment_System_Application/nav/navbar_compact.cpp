#include "navbar_compact.h"
#include "ui_navbar_compact.h"

#include <QFile>
#include <QStyle>

Navbar_compact::Navbar_compact(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Navbar_compact)
{
    ui->setupUi(this);

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

Navbar_compact::~Navbar_compact()
{
    delete ui;
}

void Navbar_compact::on_user_clicked()
{
    removeActiveItem();
    active_item = ui->user;
    addActiveItem();
    emit account_clicked();
}


void Navbar_compact::on_dashboard_clicked()
{
    removeActiveItem();
    active_item = ui->dashboard;
    addActiveItem();
    emit dashboard_clicked();
}

void Navbar_compact::on_timetracker_clicked()
{
    removeActiveItem();
    active_item = ui->timetracker;
    addActiveItem();
    emit timetracker_clicked();
}

void Navbar_compact::on_request_clicked()
{
    removeActiveItem();
    active_item = ui->request;
    addActiveItem();
    emit request_clicked();
}


void Navbar_compact::on_settings_clicked()
{
    removeActiveItem();
    active_item = ui->settings;
    addActiveItem();
    emit settings_clicked();
}


void Navbar_compact::on_login_out_button_clicked()
{
    removeActiveItem();
    active_item = ui->login_out_button;
    addActiveItem();
    emit login_out_clicked();
}


void Navbar_compact::removeActiveItem() {
    active_item->setProperty("active_item", false);
    active_item->style()->unpolish(active_item);
    active_item->style()->polish(active_item);
}

void Navbar_compact::addActiveItem() {
    active_item->setProperty("active_item", true);
    active_item->style()->unpolish(active_item);
    active_item->style()->polish(active_item);
}

void Navbar_compact::setActiveItem(QString item) {
    removeActiveItem();
    active_item = items.value(item);
    addActiveItem();
}

QString Navbar_compact::getActiveItem() {
    return items.key(active_item);
}




