#ifndef ANTRAG_DETAILPAGE_H
#define ANTRAG_DETAILPAGE_H

#include <QWidget>

namespace Ui {
class CreateAntrag;
}

class CreateAntrag : public QWidget
{
    Q_OBJECT

public:
    explicit CreateAntrag(QWidget *parent = nullptr);
    ~CreateAntrag();

private:
    Ui::CreateAntrag *ui;
};

#endif // ANTRAG_DETAILPAGE_H
