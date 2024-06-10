#ifndef ANTRAG_H
#define ANTRAG_H

#include <QObject>
#include <QDateTime>

class Antrag : public QObject
{
    Q_OBJECT
public:
    explicit Antrag(QObject *parent = nullptr, int id = -1, int employeeId = -1, QDateTime start = QDateTime::currentDateTime(), QDateTime ende = QDateTime::currentDateTime(), QString type = "", QString notiz = "", QString status = "");

    // Getter-Methoden
    int getId() const;
    int getEmployeeId() const;
    QDateTime getStart() const;
    QDateTime getEnde() const;
    QString getNotiz() const;
    QString getStatus() const;
    QString getType() const;

    // Setter-Methoden
    void setId(int id);
    void setEmployeeId(int employeeId);
    void setStart(const QDateTime &start);
    void setEnde(const QDateTime &ende);
    void setNotiz(const QString &notiz);
    void setStatus(const QString &status);
    void setType(const QString &type);


signals:


private:
    int id;
    int employeeId;
    QDateTime start;
    QDateTime ende;
    QString notiz;
    QString status;
    QString type;
};

#endif // ANTRAG_H
