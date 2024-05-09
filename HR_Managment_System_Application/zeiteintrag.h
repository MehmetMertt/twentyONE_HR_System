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
    Zeiteintrag(int id = 0, QDateTime date = QDateTime::currentDateTime(), QDateTime startzeit = QDateTime::currentDateTime(), QDateTime endzeit = QDateTime::currentDateTime(), int dauer = 0, QString notiz = "", QWidget *parent = nullptr);
    ~Zeiteintrag();

private:
    Ui::Zeiteintrag *ui;

    int id;
    QDateTime date;
    QDateTime startzeit;
    QDateTime endzeit;
    int dauer;
    QString notiz;

    void setStartzeit(QDateTime start);
    void setEndzeit(QDateTime ende);
    void setNotiz(QString notiz);

    QDateTime getStartzeit();
    QDateTime getEndzeit();
    QString getNotiz();

};

#endif // ZEITEINTRAG_H
