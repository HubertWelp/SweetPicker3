#ifndef MONITOR_H
#define MONITOR_H

#include <QMainWindow>

namespace Ui {
class MONITOR;
}

class MONITOR : public QMainWindow
{
    Q_OBJECT

public:
    explicit MONITOR(QWidget *parent = nullptr);
    ~MONITOR();

public slots:
   // void speichereParameter();


private:
    Ui::MONITOR *ui;
};

#endif // MONITOR_H
