#ifndef ANTRAG_LISTITEM_H
#define ANTRAG_LISTITEM_H

#include <QWidget>
#include "antrag.h"

namespace Ui {
class AntragListItem;
}

class AntragListItem : public QWidget
{
    Q_OBJECT

public:
    explicit AntragListItem(QWidget *parent = nullptr, Antrag* antrag = nullptr);
    ~AntragListItem();

    void updateView();

signals:
    void detailsClicked(Antrag* antrag);

private slots:
    void on_details_button_clicked();

private:
    Ui::AntragListItem *ui;

    Antrag* antrag;


};

#endif // ANTRAG_LISTITEM_H
