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
    * @return  void
    *
    */
    void anmeldeAnfrage();

    /** @brief Checkt bei jeder Tastatureingabe, ob Enter oder Escape gedrückt wurde und reagiert entsprechend
    *
    * Falls Enter gedrückt wird, wird die Methode anmeldeAnfrage() gestartet
    * Falls Escape gedrückt wird, wird das Fenster geschlosssen
    *
    * @return  void
    *
    */
    void keyPressEvent(QKeyEvent* pe) override;

private:
    Ui::Login *ui;
    Monitor m;
    KonfigAdmin k;
};
#endif // LOGIN_H
