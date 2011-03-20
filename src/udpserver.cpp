/*
 *
 *      udpserver.cpp is part of BanBot-TrackingServer
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

#include "udpserver.h"
#include "dblogger.h"

#include <QDebug>
#include <QUdpSocket>
#include <QXmlStreamReader>

UdpServer::UdpServer( QObject *parent )
    : QObject( parent )
    , m_port( 6873 )
    , m_socket( new QUdpSocket() )
    , m_dbLogger( new DbLogger() )
{
    if( !m_socket->bind( QHostAddress::Any, m_port ) ) {
        qWarning( "\e[1;31m[ERROR] UdpServer::UdpServer Couldn't bind address \e[0m" );
        return;
    }

    connect( m_socket, SIGNAL( readyRead() ), this, SLOT( parseData() ) );
}


void UdpServer::parseData()
{
    qDebug( "UdpServer::parseData" );
    while( m_socket->hasPendingDatagrams() ) {
        QByteArray rcvMsg;
        QHostAddress client;

        rcvMsg.resize( m_socket->pendingDatagramSize() );
        m_socket->readDatagram( rcvMsg.data(), rcvMsg.size(), &client );

        RemoteServerInfo remoteServer = parseXml( rcvMsg );
        remoteServer.ip = client.toString();

        // log data to server
        m_dbLogger->logServer( remoteServer );

        // use for debugging
//         qDebug() << "IFNO : " << remoteServer.ip << " " << remoteServer.name << " " << remoteServer.version << " " << remoteServer.port;
        //     qDebug() << "GAME RECIEVED DATA: " << m_data;
    }


}

UdpServer::RemoteServerInfo UdpServer::parseXml( QByteArray xmlData )
{
    RemoteServerInfo info;
    QXmlStreamReader parser( xmlData );

    while( !parser.atEnd() ) {
        parser.readNext();
        if( !parser.name().isEmpty() && parser.isStartElement() ) {
            if( parser.name().toString() != "BanBot" ) {
                QString elemName = parser.name().toString();
                parser.readNext();

                if( elemName == "serverName" )
                    info.name = parser.text().toString();
                else if( elemName == "port" )
                    info.port = parser.text().toString();
                else if( elemName == "version" )
                    info.version = parser.text().toString();
            }
        }
        else if( parser.hasError() )
                qDebug() <<  "\e[1;31m[ERROR] UdpServer::parseXml: " << parser.errorString() << "\e[0m";
    }

    return info;
}


