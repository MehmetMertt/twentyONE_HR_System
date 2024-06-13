#ifndef ANTRAG_DETAILPAGE_H
#define ANTRAG_DETAILPAGE_H

#include <QWidget>
#include "Helpers.h"
#include "antrag.h"
#include "inputvalidator.h"

namespace Ui {
class AntragDetails;
}

class AntragDetails : public QWidget
{
    Q_OBJECT

public:
    explicit AntragDetails(QWidget *parent = nullptr, Antrag* antrag = nullptr);
    ~AntragDetails();

    void setupPage(Mode mode);
    void updateView();
    void setAntrag(Antrag* antrag);

    void setPreviousPage(Mode mode);

signals:
    void antrag_submit_success(Mode mode);
    void antrag_cancel_show_requests(Mode mode);
    void antrag_cancel_show_admin();

private slots:
    void on_button_senden_clicked();

    void on_button_abbrechen_clicked();

    void on_button_ablehnen_clicked();

    void on_button_akzeptieren_clicked();

    void on_button_speichern_clicked();

private:
    Ui::AntragDetails *ui;
    InputValidator *validator;
    Antrag* antrag;

    void setInputsEnabled(bool value);
    void disableInputs();
    void enableInputs();
    void clearInputs();

    Mode previousPage;
};

#endif // ANTRAG_DETAILPAGE_H
