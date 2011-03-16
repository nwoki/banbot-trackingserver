#include "udpserver.h"

#include <QDebug>
#include <QUdpSocket>
#include <QXmlStreamReader>

UdpServer::UdpServer( QObject *parent )
    : QObject( parent )
    , m_port( 6873 )
    , m_socket( new QUdpSocket() )
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


