#ifndef TESTSENDER_H
#define TESTSENDER_H

#include <QByteArray>
#include <QObject>

class QUdpSocket;

class TestSender : public QObject
{
    Q_OBJECT
public:
    TestSender( QObject *parent = 0 );

public slots:
    void connected();
    void test( const QByteArray &msg );

private:
    QUdpSocket *m_sock;
};

#endif // TESTSENDER_H
