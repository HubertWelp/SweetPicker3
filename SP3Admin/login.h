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
    void anmeldeAnfrage();
    //void easteregg();
    void keyPressEvent(QKeyEvent* pe) override;

private:
    Ui::Login *ui;
    Monitor m;
    KonfigAdmin k;
};
#endif // LOGIN_H
