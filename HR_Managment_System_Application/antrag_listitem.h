#ifndef ANTRAG_LISTITEM_H
#define ANTRAG_LISTITEM_H

#include <QWidget>

namespace Ui {
class Antrag;
}

class Antrag : public QWidget
{
    Q_OBJECT

public:
    explicit Antrag(QWidget *parent = nullptr);
    ~Antrag();

signals:
    void detailsClicked();

private:
    Ui::Antrag *ui;
};

#endif // ANTRAG_LISTITEM_H
