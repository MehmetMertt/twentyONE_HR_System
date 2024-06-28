#ifndef ANTRAG_H
#define ANTRAG_H

#include <QObject>
#include <QDateTime>

class Antrag : public QObject
{
    Q_OBJECT
public:
    explicit Antrag(QObject *parent = nullptr, int id = -1, int employeeId = -1, QString titel = "", QDateTime start = QDateTime::currentDateTime(), QDateTime ende = QDateTime::currentDateTime(), QString reason = "", QString notiz = "", QString status = "");

    // Getter-Methoden
    int getId() const;
    int getEmployeeId() const;
    QDateTime getStart() const;
    QDateTime getEnde() const;
    QString getNotiz() const;
    QString getStatus() const;
    QString getReason() const;
    QString getTitel() const;

    // Setter-Methoden
    void setId(int id);
    void setEmployeeId(int employeeId);
    void setStart(const QDateTime &start);
    void setEnde(const QDateTime &ende);
    void setNotiz(const QString &notiz);
    void setStatus(const QString &status);
    void setReason(const QString &reason);
    void setTitel(const QString &titel);


signals:


private:
    int id;
    int employeeId;
    QString titel;
    QDateTime start;
    QDateTime ende;
    QString notiz;
    QString status;
    QString reason;
};

#endif // ANTRAG_H
