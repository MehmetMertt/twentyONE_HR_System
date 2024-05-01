#include "mainloading.h"
#include "ui_mainloading.h"

MainLoading::MainLoading(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainLoading)
{

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainLoading::hideAfterDelay);
    timer->setInterval(3000);
    timer->start();

    int screenHeight = parent->geometry().height();

    // Set initial y-position (off-screen)
    initialY = screenHeight;  // Adjust based on desired starting position

    // Move the widget initially to the off-screen position

    ui->setupUi(this);


}

MainLoading::~MainLoading()
{
    delete ui;
}

void MainLoading::hideAfterDelay() {
    timer->stop();
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
