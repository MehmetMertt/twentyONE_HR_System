#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QLineSeries>
#pragma once
#include "dbaccess.h"

namespace Ui {
class Dashboard;
}

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

private:
    Ui::Dashboard *ui;
};

#endif // DASHBOARD_H
