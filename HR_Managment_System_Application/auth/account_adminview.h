#ifndef ACCOUNT_ADMINVIEW_H
#define ACCOUNT_ADMINVIEW_H

#include <QWidget>
#include "inputvalidator.h"
#include "person.h"
#pragma once

namespace Ui {
class Account_adminview;
}

class Account_adminview : public QWidget
{
    Q_OBJECT

public:
    explicit Account_adminview(QWidget *parent = nullptr);
    ~Account_adminview();
    void initPage(int mitarbeiterID);

private:
    Ui::Account_adminview *ui;
    InputValidator *validator;

    Person* mitarbeiter;

    void loadMitarbeiter(int mitarbeiterID);
    void setDataInView();

private slots:
    void onVornameInputChanged();
    void onNachnameInputChanged();
    void onEmailInputChanged();
    void onTelefonInputChanged();
    void onAdresseInputChanged();
    void onPlzInputChanged();
    void onOrtInputChanged();
    void onPasswortInputChanged();
    void onPasswort2InputChanged();
    void on_speichern1_button_clicked();
    void on_speichern2_button_clicked();
};

#endif // ACCOUNT_ADMINVIEW_H
