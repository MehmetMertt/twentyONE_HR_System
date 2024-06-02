#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H

#include <QWidget>
#pragma once
#include "person.h"

namespace Ui {
class AdminDashboard;
}

class AdminDashboard : public QWidget
{
    Q_OBJECT

public:
    explicit AdminDashboard(QWidget *parent = nullptr);
    ~AdminDashboard();

signals:
    void new_employee_clicked();
    void edit_employee(int id);

private slots:
    void on_new_employee_button_clicked();

private:
    Ui::AdminDashboard *ui;

    void processEditMitarbeiter(int id);
};

#endif // ADMINDASHBOARD_H
