#include "testsender.h"

#include <QUdpSocket>
#include <QTimer>

TestSender::TestSender(QObject *parent)
    : QObject(parent)
    , m_sock( new QUdpSocket() )
{
    m_sock->connectToHost("80.117.69.180", 6873);

//     connect(m_sock,SIGNAL(connected()),this,SLOT(connected()));
}

void TestSender::test(const QByteArray& msg)
{
    for( int i = 0; i < 1000; i++ ) {
    qDebug("TestSender::test");
    m_sock->write(msg);
    qDebug("sent");
    }
}

void TestSender::connected()
{
    qDebug("TestSender::connected");

    QTimer::singleShot(1000, this, SLOT(test( "fuck yoou" ) ) );
}

