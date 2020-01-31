#ifndef MONITOR_H
#define MONITOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPicture>
#include <QPixmap>
#include <QFont>
#include <QMessageBox>
#include <QPushButton>
#include <QKeyEvent>

class Monitor : public QWidget
{
    Q_OBJECT
public:
    explicit Monitor(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // MONITOR_H
