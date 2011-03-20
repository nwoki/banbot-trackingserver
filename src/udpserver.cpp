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
        rcvMsg.resize( m_socket->pendingDatagramSize() );
        m_socket->readDatagram( rcvMsg.data(), rcvMsg.size() );

        // add to complete message
        m_data += rcvMsg;
    }

    // use for debugging
    qDebug() << "GAME RECIEVED DATA: " << m_data;
    m_data.clear();
}


void UdpServer::parseXml( QByteArray xmlData )
{
    /// TODO
    QXmlStreamReader parser( xmlData );
}


