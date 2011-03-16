#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>

class QUdpSocket;

class UdpServer : public QObject
{
    Q_OBJECT
public:
    UdpServer( QObject *parent = 0 );

public slots:
    /**
     * parses the data recieved
     */
    void parseData();

private:
    /**
     * parse the xml data recieved from a BanBot around the world.
     * @param xmlData data recieved
     */
    void parseXml( QByteArray xmlData );

    qint16 m_port;              /** server port. FIXED TO: 6873 */
    QByteArray m_data;          /** stash recieved data */
    QUdpSocket *m_socket;       /** the server socket */
};

#endif  // UDPSERVER_H
