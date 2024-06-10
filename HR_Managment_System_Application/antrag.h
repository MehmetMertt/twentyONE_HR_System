#ifndef ANTRAG_H
#define ANTRAG_H

#include <QObject>

class Antrag : public QObject
{
    Q_OBJECT
public:
    explicit Antrag(QObject *parent = nullptr);

signals:
};

#endif // ANTRAG_H
