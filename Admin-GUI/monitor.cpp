#include "monitor.h"

Monitor::Monitor(QWidget *parent) : QWidget(parent)
{
    QPushButton* enden = new QPushButton("beenden",this);
    QLineEdit* status = new QLineEdit("begruessend",this);
    QLabel* bild = new QLabel(this);
    QPixmap img("/home/Student/Bilder/Webcam/bearbeiteteSzene.jpg");
    bild->setPixmap(img);

    QVBoxLayout* main = new QVBoxLayout(this);
    main->addWidget(bild);
    main->addWidget(status);
    main->addWidget(enden);

    connect(enden,SIGNAL(clicked()),this,SLOT(close()));

    setLayout(main);
}
