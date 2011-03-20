/*
 *
 *      main.cpp is part of BanBot-TrackingServer
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

#include <QtCore/QCoreApplication>

#include "udpserver.h"
#include "../testSender/testsender.h"

int main( int argc, char *argv[] )
{
    QCoreApplication a( argc, argv );

    UdpServer *udpServer = new UdpServer();
//     TestSender asd;
//     asd.test( "<BanBot><serverName>asd</serverName><version>aadddccc</version></BanBot>" );
    return a.exec();
}
