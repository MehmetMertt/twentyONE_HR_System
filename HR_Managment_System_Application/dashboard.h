#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QLineSeries>
#pragma once
#include "dbaccess.h"
#include <QDateTime>
#include "timetracker.h"

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

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dashboard *ui;
    void updateGreeting();
     QFrame *myFrame;
};

#endif // DASHBOARD_H
