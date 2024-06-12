#ifndef ZEITEINTRAG_H
#define ZEITEINTRAG_H

#include <QWidget>
#include <QDateTime>
#include "inputvalidator.h"
#pragma once

namespace Ui {
class Zeiteintrag;
}

class Zeiteintrag : public QWidget
{
    Q_OBJECT

public:
    Zeiteintrag(QWidget *parent = nullptr);
    Zeiteintrag(int employeeId = 0, QDateTime startzeit = QDateTime::currentDateTime(), QDateTime endzeit = QDateTime::currentDateTime(), double dauer = 0, QString notiz = "", QWidget *parent = nullptr);



    ~Zeiteintrag();
    void setStartzeit(QDateTime start);
    void setEndzeit(QDateTime ende);
    void setNotiz(QString notiz);
    void setEmployeeId(int employeeId);
    void setTimentryId(int id);

    QDateTime getStartzeit();
    QDateTime getEndzeit();
    QString getNotiz();
    int getEmployeeId();
    int getTimeentryId();
    void compareDatum();

signals:
    void editZeiteintrag(Zeiteintrag* zeiteintrag);

private slots:
    void on_button_edit_clicked();

    void on_cancel_clicked();

    void on_save_clicked();

    void on_startzeit_edit_dateTimeChanged();
    void on_endzeit_edit_dateTimeChanged();
    void on_notiz_edit_textChanged();

    void on_remove_clicked();

private:
    Ui::Zeiteintrag *ui;
    InputValidator *validator;
    int employeeId;
    QDateTime startzeit;
    QDateTime endzeit;
    double dauer;
    QString notiz;
    int timeentryId;

    void updateView();


};

#endif // ZEITEINTRAG_H
