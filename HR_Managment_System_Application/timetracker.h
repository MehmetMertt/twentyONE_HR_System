#ifndef TIMETRACKER_H
#define TIMETRACKER_H

#include <QWidget>
#include <QList>
#include <QPair>
#include <QDateTime>
#include "timestamp.h"
#include "QListWidgetItem"
#include "zeiteintrag.h"
#pragma once

namespace Ui {
class Timetracker;
}

class Timetracker : public QWidget
{
    Q_OBJECT

public:
    explicit Timetracker(QWidget *parent = nullptr);
    ~Timetracker();

    void loadData();

signals:
    void openEditZeiteintrag(QList<Timestamp*> timestamps);

private slots:
    void on_button_start_clicked();

    void on_button_pause_clicked();

    void on_button_stop_clicked();

    void on_button_weiter_clicked();

    void on_button_neu_clicked();

private:
    Ui::Timetracker *ui;

    QList<Timestamp*> timestamps;
    void updateTimer();
    bool timer_running = false;
    int elapsedTime = 0;

    QMap<Zeiteintrag*, QListWidgetItem*> listitems;

    QTimer *timer;

    void resizeListItem(Zeiteintrag* zeiteintrag);

    void loadTimeentries();
    void loadDashboardData();

    int wochenstunden;
    int ueberstunden;

};

#endif // TIMETRACKER_H
