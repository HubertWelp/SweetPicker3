#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMessageBox>
#include "monitor.h"
#include "konfig.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LOGIN; }
QT_END_NAMESPACE

class LOGIN : public QMainWindow
{
    Q_OBJECT

public:
    LOGIN(QWidget *parent = nullptr);
    ~LOGIN() override;

public slots:
    void anmeldeAnfrage();
    //void easteregg();
    void keyPressEvent(QKeyEvent* pe) override;

private:
    Ui::LOGIN *ui;
    MONITOR m;
    KonfigAdmin k;
};
#endif // LOGIN_H
