#ifndef TIMETRACKER_H
#define TIMETRACKER_H

#include <QWidget>
#include <QList>
#include <QPair>
#include <QDateTime>

namespace Ui {
class Timetracker;
}

class Timetracker : public QWidget
{
    Q_OBJECT

public:
    explicit Timetracker(QWidget *parent = nullptr);
    ~Timetracker();

private slots:
    void on_button_start_clicked();

    void on_button_pause_clicked();

    void on_button_stop_clicked();

    void on_button_weiter_clicked();

private:
    Ui::Timetracker *ui;

    QList<QPair<QDateTime, QDateTime>> timestamps;
    void updateTimer();
    bool timer_running = false;
    int elapsedTime = 0;

    QTimer *timer;
};

#endif // TIMETRACKER_H
