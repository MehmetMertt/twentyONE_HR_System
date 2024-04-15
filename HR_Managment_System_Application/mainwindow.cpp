#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    navbar = new Navbar(this);
    //login_page = new Login(this);
    //ui->main->addWidget(login_page);
    ui->open_nav_button->hide();
    ui->nav_line->hide();
    ui->sidebar->addWidget(navbar);

    // Load the stylesheet from a file (recommended)
    QString stylesheetPath = ":main/main_stylesheet.qss"; // Assuming your stylesheet is in a resources file named "login.qss"
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

    navbar_geometry = QRect(navbar->geometry().x(), navbar->geometry().y(), navbar->geometry().width(), navbar->geometry().height());

    // Animate the width from the current value to 0 (hidden)
    animation->setStartValue(navbar->geometry());
    animation->setEndValue(QRect(navbar->geometry().x(), navbar->geometry().y(), 0, navbar->geometry().height()));

    // Connect the animation's finished signal to show the open button
    connect(animation, &QPropertyAnimation::finished, [this]() {
        navbar->hide();
        ui->nav_line->show();
        ui->close_nav_button->hide();
        ui->open_nav_button->show();
    });

    // Start the animation
    animation->start();
}


void MainWindow::on_open_nav_button_clicked()
{
    // Create a property animation for the sidebar's width
    QPropertyAnimation *animation = new QPropertyAnimation(navbar, "geometry");
    animation->setDuration(200); // 100ms animation duration

    // Animate the width from 0 (hidden) to the current sidebar width
    animation->setStartValue(QRect(navbar->geometry().x(), navbar->geometry().y(), 0, navbar->geometry().height()));
    animation->setEndValue(navbar_geometry);

    // Connect the animation's finished signal to hide the open button
    connect(animation, &QPropertyAnimation::finished, [this]() {
        navbar->show();
        ui->nav_line->hide();
        ui->close_nav_button->show();
        ui->open_nav_button->hide();
    });

    // Start the animation
    animation->start();
}

