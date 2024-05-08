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

private:
    Ui::Zeiteintrag *ui;
};

#endif // ZEITEINTRAG_H
