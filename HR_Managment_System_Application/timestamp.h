#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <QObject>
#include <QDateTime>

class Timestamp : public QObject
{
    Q_OBJECT
public:
    Timestamp(QObject *parent = nullptr, QDateTime start = QDateTime::currentDateTime(), QDateTime ende = QDateTime::currentDateTime());

    QPair<QDateTime, QDateTime> data;

signals:

private:

};

#endif // TIMESTAMP_H
