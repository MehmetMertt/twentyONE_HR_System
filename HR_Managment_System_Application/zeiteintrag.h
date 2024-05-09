#ifndef ZEITEINTRAG_H
#define ZEITEINTRAG_H

#include <QWidget>

namespace Ui {
class Zeiteintrag;
}

class Zeiteintrag : public QWidget
{
    Q_OBJECT

public:
    explicit Zeiteintrag(QWidget *parent = nullptr);
    ~Zeiteintrag();
    void setStartzeit(QDateTime startzeit);
    void setEndzeit(QDateTime endzeit);
    void setNotiz(QString notiz);

    QDateTime getStartzeit();
    QDateTime getEndzeit();
    QString getNotiz();

private:
    Ui::Zeiteintrag *ui;

    QDateTime startzeit;
    QDateTime endzeit;
    QString notiz;
};

#endif // ZEITEINTRAG_H
