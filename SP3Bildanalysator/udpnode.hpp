
#ifndef UDPNODE_H
#define UDPNODE_H

#include <QObject>
#include <QUdpSocket>
#include <string>
/** @class UDPNode
 * @brief Receive and transmit string messages over UDP
 *
 * Simple class that provides methods to receive and transmit text messages over a single port using the UDP protocol.
 * The using class can thus take the role as a UDP-server (waiting  for incoming messages and receiving them) or as a UDP-client
 * (initiating a contact by sending a message to the UDP-server). The standard server port number is 5842. This number is also
 * used as the standard port number for the receiver when sending a message.
 * UDPNode needs Qt, since it's implementation is based on the Qt network modul.
 *
 * UDPNode can be used in two ways.
 * 1. If the hosting part of the program uses Qt, UDPNode should be integrated by instantiating a variable of this class and
 * connect the signal msgReceivedSignal(QString) with an appropriate slot.
 * 2. If the hosting part of the program does not use Qt, UDPNode has to be integrated via inheritance. A class must be derived
 * from UDPNode which redefines the inherited virtual method void messageReceived(std::string msg).
 *
 * @author Dr. Hubert Welp
 *
 */
class UDPNode : public QObject
{
    Q_OBJECT
public:
    virtual ~UDPNode();
    /** @brief construktor
    *
    * Initalizes the communication socket with a port number. This number must be known by the clients.
    *
    * @param [in] port The port number to be used for the communication socket.
    *
    */
    explicit UDPNode(unsigned short port=5842,QObject *parent = nullptr);
    /** @brief send a text message
    *
    * Sends a text message to a specified destination.
    *
    * @param [in] msg The text to be transmitted
    * @param [in] destIpAdress The IP-adress of the receiving server host
    * @param [in] desPortNr The port number of the receiving server program
    */
    void sendmessage(std::string msg,const std::string destIpAdress="172.20.10.79",const unsigned short destPortNr=5843);
//    void setCallback(void (*cb)(std::string msg));
Q_SIGNALS:
    /** @brief Qt-Signal emitted on message reception
    *
    * Each time a message is received from the UDP socket this signal will be emitted.
    *
    * @param [in] message The text received from the socket
    */
    void msgReceivedSignal(QString message);
public Q_SLOTS:
    void processPendingDatagrams();
protected:
    /** @brief called on message reception
    *
    * Each time a message is received from the UDP socket this method is called. This class's implementation only
    * outputs the message on the console. The method should be redefined in a class derived from UDPNode. In the redefined
    * method the the user requested functionality can be implemented.
    *
    * @param [in] msg The text received from the socket
    */
    virtual void messageReceived(std::string msg);

private:
    QUdpSocket socket;
//    void (*msgReceivedCallback)(std::string msg);
};

#endif // UDPNODE_H
