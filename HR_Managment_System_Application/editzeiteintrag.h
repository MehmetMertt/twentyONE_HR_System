#ifndef EDITZEITEINTRAG_H
#define EDITZEITEINTRAG_H

#include <QWidget>
#include <editzeiteintragitem.h>
#include <timestamp.h>

namespace Ui {
class EditZeiteintrag;
}

class EditZeiteintrag : public QWidget
{
    Q_OBJECT

public:
    explicit EditZeiteintrag(QWidget *parent = nullptr);
    ~EditZeiteintrag();

    void initPage(QList<Timestamp*> timestamps);

private slots:
    void on_save_clicked();

private:
    Ui::EditZeiteintrag *ui;

    QList<EditZeiteintragItem*> timestampItems;

    void saveZeiteintrag();
};

#endif // EDITZEITEINTRAG_H
