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
    navbar_comp = new Navbar_compact(this);
    //login_page = new Login(this);
    //ui->main->addWidget(login_page);
    ui->sidebar->addWidget(navbar_comp);
    navbar_comp->hide();
    ui->open_nav_button->hide();
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
    animation->setEndValue(navbar_comp->geometry());

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

