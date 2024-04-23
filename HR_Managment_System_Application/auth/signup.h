#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>

#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QLineEdit>

namespace Ui {
class Signup;
}

class Signup : public QWidget
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = nullptr);
    ~Signup();

    //Fürs erste mal hier: (vllt später in private und dann mit getter und setter)
    QValidator *Vorname_validator;
    QValidator *Nachname_validator;
    QValidator *Email_validator;
    QValidator *Telefon_validator;
    QValidator *Plz_validator;
    QValidator *Ort_validator;
    QValidator *Passwort_validator;

    void setVorname_erlaubt(bool true_false){ Vorname_erlaubt = true_false; }
    bool getVorname_erlaubt(){ return Vorname_erlaubt; }
    void setNachname_erlaubt(bool true_false){ Nachname_erlaubt = true_false; }
    bool getNachname_erlaubt(){ return Nachname_erlaubt; }
    void setEmail_erlaubt(bool true_false){ Email_erlaubt = true_false; }
    bool getEmail_erlaubt(){ return Email_erlaubt; }
    void setTelefon_erlaubt(bool true_false){ Telefon_erlaubt = true_false; }
    bool getTelefon_erlaubt(){ return Telefon_erlaubt; }
    void setPlz_erlaubt(bool true_false){ Plz_erlaubt = true_false; }
    bool getPlz_erlaubt(){ return Plz_erlaubt; }
    void setOrt_erlaubt(bool true_false){ Ort_erlaubt = true_false; }
    bool getOrt_erlaubt(){ return Ort_erlaubt; }
    void setPasswort_erlaubt(bool true_false){ Passwort_erlaubt = true_false; }
    bool getPasswort_erlaubt(){ return Passwort_erlaubt; }

private slots:
    void on_signup_button_clicked();
    void ueberpruefeVorname();
    void ueberpruefeNachname();
    void ueberpruefeEmail();
    void ueberpruefeTelefon();
    void ueberpruefePlz();
    void ueberpruefeOrt();
    void ueberpruefePasswort();
    void alleEingabenCheck();

private:
    Ui::Signup *ui;
    bool Vorname_erlaubt;
    bool Nachname_erlaubt;
    bool Email_erlaubt;
    bool Telefon_erlaubt;
    bool Plz_erlaubt;
    bool Ort_erlaubt;
    bool Passwort_erlaubt;
};

#endif // SIGNUP_H
