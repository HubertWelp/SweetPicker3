#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMessageBox>
#include "monitor.h"
#include "konfig.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login() override;

public slots:
    /** @brief Überprüft, ob der eingegbene Text mit dem Passwort übereinstimmt
    *
    * Diese Methode liest den eingegeben Text in der Zeile für das Passwort und überprüft, ob es
    * mit dem Passwort aus der konfig.ini Datei übereinstimmt
    *
    * @param [in] nr Nummer des Objektes,
    *
    * @return  Liefert den Namen des Objektes mit der jeweiligen Objektnummer, falls es einen Objektnamen zu dieser Objektnummer gibt
    *          Falls es zu der Objektnummer keinen Objektnamen gibt, wird ein Leerstring ("") zurückgegeben.
    *
    */
    void anmeldeAnfrage();
    //void easteregg();
    void keyPressEvent(QKeyEvent* pe) override;

private:
    Ui::Login *ui;
    Monitor m;
    KonfigAdmin k;
};
#endif // LOGIN_H
