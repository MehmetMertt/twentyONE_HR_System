#ifndef ZEITEINTRAG_H
#define ZEITEINTRAG_H

#include <QWidget>
#include <QDateTime>

namespace Ui {
class Zeiteintrag;
}

class Zeiteintrag : public QWidget
{
    Q_OBJECT

public:
    Zeiteintrag(QWidget *parent = nullptr);
    Zeiteintrag(int id = 0, QDateTime date = QDateTime::currentDateTime(), QDateTime start = QDateTime::currentDateTime(), QDateTime ende = QDateTime::currentDateTime(), int duration = 0, QString comment = "", QWidget *parent = nullptr);
    ~Zeiteintrag();

private:
    Ui::Zeiteintrag *ui;

    int id;
    QDateTime date;
    QDateTime start;
    QDateTime ende;
    int duration;
    QString comment;

};

#endif // ZEITEINTRAG_H
