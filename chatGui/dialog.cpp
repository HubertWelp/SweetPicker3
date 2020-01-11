#include "dialog.h"
#include "ui_dialog.h"
#include <iostream>
Dialog::Dialog(std::string destIpAdress,unsigned short destPort,unsigned short localPort,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    node(localPort),
    zielIp(destIpAdress),
    zielPort(destPort)
{
    ui->setupUi(this);
    connect(&node,&UDPNode::msgReceivedSignal,this,&Dialog::messageReceived);
    connect(ui->sendButton,&QPushButton::clicked,this,&Dialog::sendMessage);
//    node.setCallback(&Dialog::messageReceivedCallback);
}

Dialog::~Dialog()
{
    delete ui;
}

//void Dialog::messageReceivedCallback(std::string msg)
//{
//    messageReceived(QString::fromStdString(msg));
//}

void Dialog::sendMessage()
{
    QString alt;
    alt=ui->textBrowser->toPlainText()+"\n<<<";
    ui->textBrowser->setText(alt+ui->textEingabe->toPlainText());
    std::cout << ui->textEingabe->toPlainText().toStdString() << std::endl;
    node.sendmessage(ui->textEingabe->toPlainText().toStdString(),zielIp,zielPort);
    ui->textEingabe->clear();
}

void Dialog::messageReceived(QString msg)
{
    QString alt;
    alt=ui->textBrowser->toPlainText()+"\n>>>";
    ui->textBrowser->setText(alt+msg);
}
