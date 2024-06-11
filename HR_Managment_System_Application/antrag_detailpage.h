#ifndef ANTRAG_DETAILPAGE_H
#define ANTRAG_DETAILPAGE_H

#include <QWidget>
#include "Helpers.h"
#include "antrag.h"

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

signals:
    void antrag_submit_success(Mode mode);
    void antrag_cancel(Mode mode);

private slots:
    void on_button_senden_clicked();

    void on_button_abbrechen_clicked();

private:
    Ui::AntragDetails *ui;

    Antrag* antrag;

    void setInputsEnabled(bool value);
    void disableInputs();
    void enableInputs();
    void clearInputs();
};

#endif // ANTRAG_DETAILPAGE_H
