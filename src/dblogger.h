/*
 *
 *      dblogger.h is part of BanBot-TrackingServer
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
 *
 *      Description: this class is used to log data to an sqlite database
 */

#ifndef DBLOGGER_H
#define DBLOGGER_H

#include "udpserver.h"

#include <QSqlDatabase>

class DbLogger : public QSqlDatabase
{
public:
    DbLogger();

    /**
     * logs server info to database
     * @param remoteServer server struct information to log to database
     */
    void logServer( const UdpServer::RemoteServerInfo &remoteServer );

private:
    void setup();       /** sets up database and check's for it's existance */

    QString m_dbDir     /** default database values. These are given on class initialization in the .cpp */
    , m_dbName;
};

#endif  // DBLOGGER_H