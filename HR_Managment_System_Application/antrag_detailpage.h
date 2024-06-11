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

private:
    Ui::AntragDetails *ui;

    Antrag* antrag;
};

#endif // ANTRAG_DETAILPAGE_H
