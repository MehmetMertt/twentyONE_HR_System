#ifndef EDITZEITEINTRAGITEM_H
#define EDITZEITEINTRAGITEM_H

#include <QWidget>
#include <QDateTime>
#include "timestamp.h"
#include "inputvalidator.h"

namespace Ui {
class EditZeiteintragItem;
}

class EditZeiteintragItem : public QWidget
{
    Q_OBJECT

public:
    explicit EditZeiteintragItem(QWidget *parent = nullptr);
    EditZeiteintragItem(QWidget *parent = nullptr, int id = -1, Timestamp* timestamp = nullptr);
    ~EditZeiteintragItem();

    QDateTime getStartzeit();
    QDateTime getEndzeit();
    QString getNotiz();
    int getID();
    void compareDatum();
    InputValidator *validator;

public slots:
    void updateTimestamp();

    void onStartzeitChanged();
    void onEndzeitChanged();
    void onNotizChanged();

private:
    Ui::EditZeiteintragItem *ui;
    int id;
    Timestamp* timestamp;

    void initPage();

};

#endif // EDITZEITEINTRAGITEM_H
