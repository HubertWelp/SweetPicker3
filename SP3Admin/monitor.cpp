#include "monitor.h"
#include "ui_monitor.h"

MONITOR::MONITOR(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MONITOR)
{
    ui->setupUi(this);
}

MONITOR::~MONITOR()
{
    delete ui;
}
