#ifndef MITARBEITERVIEW_H
#define MITARBEITERVIEW_H

#include <QWidget>

#include "person.h"
#pragma once

namespace Ui {
class MitarbeiterView;
}

class MitarbeiterView : public QWidget
{
    Q_OBJECT

public:
    MitarbeiterView(QWidget *parent = nullptr, int id = -1, Person* mitarbeiter = nullptr);
    ~MitarbeiterView();

signals:
    void editEmployee(int);

private slots:
    void on_button_edit_clicked();

private:
    Ui::MitarbeiterView *ui;

    int id;

    Person* mitarbeiter;

    void initData();
};

#endif // MITARBEITERVIEW_H
