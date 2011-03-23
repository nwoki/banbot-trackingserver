/*
 *
 *      dblogger.cpp is part of BanBot-TrackingServer
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

#include "dblogger.h"

#include <QDebug>
#include <QDir>
#include <QDate>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

#define SERVERS_TABLE "create table servers( id INTEGER PRIMARY KEY, name TEXT, ip TEXT, port TEXT, version TEXT, firstRecDate TEXT, lastRecDate TEXT );"

DbLogger::DbLogger()
    : QSqlDatabase( QSqlDatabase::addDatabase( "QSQLITE" ) )
    , m_dbDir( "database" )
    , m_dbName( "trackingStats.sqlite" )
{
    setup();
}

void DbLogger::logServer( const UdpServer::RemoteServerInfo& remoteServer )
{
    qDebug( "DbLogger::logServer" );

    if( !isOpen() ) {
        qDebug( "opening connection to database " );
        if( !open() ) {
            qDebug( "\e[1;31m[ERROR] DbLogger::logServer can't open connection to db \e[0m" );
            return;
        }
    }
    QSqlQuery query;

    QString checkQuery( "select id from servers where ip='" + remoteServer.ip + "' and port='" + remoteServer.port + "';" );
    if( !query.exec( checkQuery ) ) {
        qDebug() << "\e[1;31m[ERROR] DbLogger::logServer can't execute query:'" << checkQuery << " : " << query.lastError().text() << "\e[0m";
        return;
    }

    // check for values
    // server not in database, add
    if( !query.next() ) {
        QString insertQuery( "insert into servers(name,ip,port,version,firstRecDate,lastRecDate) values( " );
        insertQuery.append( "'" + remoteServer.name + "'," );
        insertQuery.append( "'" + remoteServer.ip + "'," );
        insertQuery.append( "'" + remoteServer.port + "'," );
        insertQuery.append( "'" + remoteServer.version + "'," );
        insertQuery.append( "'" + QDate::currentDate().toString( "ddd d MMMM yyyy" ) + "'," );
        insertQuery.append( "'" + QDate::currentDate().toString( "ddd d MMMM yyyy" ) + "');" );

        if( !query.exec( insertQuery ) ) {
            qDebug() << "\e[1;31m[ERROR] DbLogger::logServer can't execute query:'" << insertQuery << " : " << query.lastError().text() << "\e[0m";
            return;
        }
    } else {  // update server values
        QString id = query.value(0).toString();
        QString updateQuery( "update servers set name='" );
        updateQuery.append( remoteServer.name );
        updateQuery.append( "',lastRecDate='" );
        updateQuery.append( QDate::currentDate().toString( "ddd d MMMM yyyy" ) );
        updateQuery.append( "' where id='" );
        updateQuery.append( id );
        updateQuery.append( "';" );

        if( !query.exec( updateQuery ) ) {
            qDebug() << "\e[1;31m[ERROR] DbLogger::logServer can't execute query:'" << updateQuery << " : " << query.lastError().text() << "\e[0m";
            return;
        }
    }
}

void DbLogger::setup()
{
    qDebug( "DbController::setup" );
    bool createTable = false;

    // check if database folder exists
    if( !QDir().exists( m_dbDir ) ) {
        if( !QDir().mkdir( m_dbDir ) ) { //create directory
            qWarning( "\e[1;31mDbLogger::setup can't create folder for database. Check permissions\e[0m" );
            return;
        }
    }

    qDebug() << "setting db name to: " << m_dbDir + QDir::separator() + m_dbName;
    setDatabaseName( m_dbDir + QDir::separator() + m_dbName );

    // check if database file exists
    if( QFile::exists( m_dbDir + QDir::separator() + m_dbName ) ) {
        qWarning( "\e[0;33mDbLogger::setup found database.. skipping setup\e[0m" );
        return;
    }
    else
        createTable = true;

    //check database was set correctly
    if( databaseName().isEmpty() ) {
        qWarning( "\e[1;31mDbLogger::setup can't load database name setting.\e[0m" );
        return;
    }

    //open database to check everything was set correctly
    if ( !open() ) {
        qWarning( "\e[1;31mDbLogger::setup can't create connection to SQLITE database: \"%s\"\e[0m", qPrintable( lastError().text() ) );
        return;
    }

    // create database
    if( createTable ) {
        QSqlQuery query;
        if( !query.exec( SERVERS_TABLE ) ) {
            qDebug() << "\e[1;31mDbLogger::setup FAILED to execute query ( servers table ): " << query.lastError().text() << "\e[0m" ;
            return;
        }
    }

    close();
}

