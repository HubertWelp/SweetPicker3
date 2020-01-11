#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "udpnode.hpp"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(std::string destIpAdress,unsigned short destPort,unsigned short localPort, QWidget *parent = nullptr);
    ~Dialog();
//    void messageReceivedCallback(std::string msg);

private:
    Ui::Dialog *ui;
    std::string zielIp;
    unsigned short zielPort;
    UDPNode node;

protected slots:
    void sendMessage();
    void messageReceived(QString msg);
};

#endif // DIALOG_H
