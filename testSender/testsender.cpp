#include "testsender.h"

#include <QUdpSocket>
#include <QTimer>

TestSender::TestSender(QObject *parent)
    : QObject(parent)
    , m_sock( new QUdpSocket() )
{
    m_sock->connectToHost("127.0.0.1", 6873);
}

void TestSender::test(const QByteArray& msg)
{
    qDebug( "TestSender::test" );
    m_sock->write(msg);
}


