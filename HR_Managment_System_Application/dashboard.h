#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QLineSeries>
#pragma once
#include <QDateTime>
#include <QFrame>

namespace Ui {
class Dashboard;
}

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

    void loadData();

signals:
    void goZeitaufzeichnung();
    void stopZeitaufzeichnung();

private slots:
    void on_startTracker_clicked();
    void on_stopTracker_clicked();

private:
    Ui::Dashboard *ui;
    void updateGreeting();
    QFrame *myFrame;
};

#endif // DASHBOARD_H
