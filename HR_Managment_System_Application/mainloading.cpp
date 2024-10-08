#include "mainloading.h"
#include "ui_mainloading.h"
#include <QThread>

#include <dbaccess.h>

MainLoading::MainLoading(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainLoading)
{

    /*timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainLoading::hideAfterDelay);
    timer->setInterval(100);
    timer->start();*/
    int screenHeight = parent->geometry().height();

    // Set initial y-position (off-screen)
    initialY = screenHeight;  // Adjust based on desired starting position


    ui->setupUi(this);







}

MainLoading::~MainLoading()
{
    delete ui;
}

void MainLoading::loadDB() {
    dbZugriff = new dbmanager();
    general_wochenstunden = 38.5;
    //dbZugriff->addMitarbeiter("Flo", "Mimmler", "fmimmler@gmail.com", "+43 67006070522", "Test123!","Ringstraße 0",1230,"Wien","Herr");
    QThread::sleep(1);
    hideWhenReady();
}

void MainLoading::hideWhenReady() {
    //qDebug("hide loading page");
    //timer->stop();
    emit loadingFinished();
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(1000);  // Adjust duration for slide-up speed
    animation->setStartValue(QRect(x(), y(), width(), height()));
    animation->setEndValue(QRect(x(), initialY, width(), height()));  // Slide to top of screen
    animation->setEasingCurve(QEasingCurve::OutCubic);  // Use an easing curve for smooth movement

    // Connect animation finished signal to hide the widget and emit loadingFinished
    connect(animation, &QPropertyAnimation::finished, this, &MainLoading::hide);

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
