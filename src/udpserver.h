/*
 *      udpserver.h is part of BanBot-TrackingServer
 *
 *      BanBot-TrackingServer is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 *
 *      BanBot-TrackingServer is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with BanBot-TrackingServer (look at GPL_License.txt).
 *      If not, see <http://www.gnu.org/licenses/>.
 *
 *      Copyright © 2011 Francesco Nwokeka( n3m3s1s )
 *      Author           Francesco Nwokeka
 */


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
