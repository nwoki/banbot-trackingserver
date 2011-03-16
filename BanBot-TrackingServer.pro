#-------------------------------------------------
#
# Project created by QtCreator 2011-03-10T20:41:46
#
#-------------------------------------------------

QT += core \
      network

QT -= gui

TARGET = BanBot-TrackingServer
CONFIG += console \
          debug

CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
        src/main.cpp \
        src/udpserver.cpp \
        src/testsender.cpp

HEADERS += \
        src/udpserver.h \
        src/testsender.h

OBJECTS_DIR = .obj