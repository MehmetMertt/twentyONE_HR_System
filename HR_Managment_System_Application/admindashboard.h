#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H

#include <QWidget>
#pragma once
#include "person.h"
#include <Helpers.h>
#include "antrag_listitem.h"
#include <antrag.h>

namespace Ui {
class AdminDashboard;
}

class AdminDashboard : public QWidget
{
    Q_OBJECT

public:
    explicit AdminDashboard(QWidget *parent = nullptr);
    ~AdminDashboard();

    void updateView(Mode mode);
    void updateView();




signals:
    void new_employee_clicked();
    void edit_employee(int id);
    void showAntragDetailPage(Mode mode, Antrag* antrag);


private slots:
    void on_new_employee_button_clicked();

private:
    Ui::AdminDashboard *ui;
    QTimer *timer;
    void processAntragDetailClicked(Antrag* antrag);
    void insertRequests();

    void processEditMitarbeiter(int id);
    void updateEmployeeList();
    void updateAntragList();
    void updateGeneralData();
};

#endif // ADMINDASHBOARD_H
