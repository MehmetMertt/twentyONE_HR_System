#ifndef MAINLOADING_H
#define MAINLOADING_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QPropertyAnimation>
#pragma once

namespace Ui {
class MainLoading;
}

class MainLoading : public QWidget
{
    Q_OBJECT

public:
    explicit MainLoading(QWidget *parent = nullptr);
    ~MainLoading();
    void loadDB();

    signals:
        void loadingFinished();

private slots:
    void hideWhenReady();


private:
    Ui::MainLoading *ui;
    QLabel *label;
    QTimer *timer;
    int initialY;
};

#endif // MAINLOADING_H
