#ifndef ZEITEINTRAG_H
#define ZEITEINTRAG_H

#include <QWidget>
#include <QDateTime>
#pragma once

namespace Ui {
class Zeiteintrag;
}

class Zeiteintrag : public QWidget
{
    Q_OBJECT

public:
    Zeiteintrag(QWidget *parent = nullptr);
    Zeiteintrag(int id = 0, QDateTime date = QDateTime::currentDateTime(), QDateTime startzeit = QDateTime::currentDateTime(), QDateTime endzeit = QDateTime::currentDateTime(), double dauer = 0, QString notiz = "", QWidget *parent = nullptr);



    ~Zeiteintrag();
    void setStartzeit(QDateTime start);
    void setEndzeit(QDateTime ende);
    void setNotiz(QString notiz);
    void setEmployeeId(int id);
    void setTimentryId(int id);

    QDateTime getStartzeit();
    QDateTime getEndzeit();
    QString getNotiz();
    int getEmployeeId();
    int getTimeentryId();

private:
    Ui::Zeiteintrag *ui;

    int employeeId;
    QDateTime date;
    QDateTime startzeit;
    QDateTime endzeit;
    double dauer;
    QString notiz;
    int timeentryId;



};

#endif // ZEITEINTRAG_H
