#include "udpnode.hpp"
#include <iostream>
#include <QDataStream>
#include <QDebug>
#include <QObject>
UDPNode::~UDPNode()
{

}

UDPNode::UDPNode(unsigned short serverPort,QObject *parent) : QObject(parent)
{
//    msgReceivedCallback=nullptr;
    socket.bind(serverPort);
//    connect(&socket,&QUdpSocket::readyRead,this,&UDPNode::processPendingDatagrams);
    connect(&socket,SIGNAL(readyRead()),this,SLOT(processPendingDatagrams()));
}

void UDPNode::processPendingDatagrams()
{
    QByteArray datagram;
    QString msg;

    do
    {
        datagram.resize(socket.pendingDatagramSize());
        socket.readDatagram(datagram.data(),datagram.size());
    }while(socket.hasPendingDatagrams());
    QDataStream in(&datagram,QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_8);
    in >> msg;

    messageReceived(msg.toStdString());
//    std::cout << msg.toStdString() << endl;
    Q_EMIT msgReceivedSignal(msg);
//    if(msgReceivedCallback)
//        msgReceivedCallback(msg.toStdString());
}

void UDPNode::messageReceived(std::string msg)
{

}

void UDPNode::sendmessage(std::string msg,const std::string destIpAdress,const unsigned short destPortNr)
{
    QHostAddress ipAdress;
    quint16 portNr;
    ipAdress.setAddress(QString::fromStdString(destIpAdress));
    portNr=destPortNr;

    QByteArray datagram;
    QDataStream out(&datagram,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
//    std::cout << msg << std::endl;
    out << QString::fromStdString(msg);

    socket.writeDatagram(datagram,ipAdress,portNr);
}

//void UDPNode::setCallback(void (*cb)(std::string))
//{
//    if(cb)
//        msgReceivedCallback=cb;
//}

