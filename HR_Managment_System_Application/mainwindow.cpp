#include "mainwindow.h"
#include "ui_mainwindow.h"
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

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

    db.setHostName("localhost");
    db.setDatabaseName("hr_management_system");
    db.setUserName("admin");
    db.setPassword("admin");
    bool ok = db.open();
    qInfo() << ok;

    navbar = new Navbar(this);
    navbar_comp = new Navbar_compact(this);
    //login_page = new Login(this);
    signup_page = new Signup(this);
    //ui->main->addWidget(login_page);

    ui->main->addWidget(signup_page);

    ui->open_nav_button->hide();
    ui->sidebar->addWidget(navbar);
    ui->sidebar->addWidget(navbar_comp);
    navbar_comp->hide();

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

MainWindow::~MainWindow()
{

    delete ui;
}



void MainWindow::on_close_nav_button_clicked()
{
    // Create a property animation for the sidebar's width
    QPropertyAnimation *animation = new QPropertyAnimation(navbar, "geometry");
    animation->setDuration(150); // 100ms animation duration

    navbar_geometry = QRect(ui->sidebar->geometry().x(), ui->sidebar->geometry().y(), navbar->geometry().width(), ui->sidebar->geometry().height());

    // Animate the width from the current value to 0 (hidden)
    animation->setStartValue(navbar->geometry());
    animation->setEndValue(navbar_geometry);

    // Connect the animation's finished signal to show the open button
    connect(animation, &QPropertyAnimation::finished, [this]() {
        navbar->hide();
        navbar_comp->show();
        ui->close_nav_button->hide();
        ui->open_nav_button->show();
    });

    // Start the animation
    animation->start();
}


void MainWindow::on_open_nav_button_clicked()
{
    navbar_comp->hide();
    navbar->show();
    // Create a property animation for the sidebar's width
    QPropertyAnimation *animation = new QPropertyAnimation(navbar, "geometry");
    animation->setDuration(200); // 100ms animation duration

    navbar_geometry = QRect(ui->sidebar->geometry().x(), ui->sidebar->geometry().y(), navbar_comp->geometry().width(), ui->sidebar->geometry().height());

    // Animate the width from 0 (hidden) to the current sidebar width
    animation->setStartValue(navbar_comp->geometry());
    animation->setEndValue(navbar_geometry);

    // Connect the animation's finished signal to hide the open button
    connect(animation, &QPropertyAnimation::finished, [this]() {
        ui->close_nav_button->show();
        ui->open_nav_button->hide();
    });

    // Start the animation
    animation->start();
}

