######################################################################
# Automatically generated by qmake (3.1) Sat Oct 5 12:03:21 2024
######################################################################

TEMPLATE = app
TARGET = lab2
INCLUDEPATH += .
INCLUDEPATH += /opt/Qt/5.15.2/gcc_64/include/
INCLUDEPATH += /opt/Qt/5.15.2/gcc_64/include/QtWidgets
INCLUDEPATH += /opt/Qt/5.15.2/gcc_64/include/QtCore
INCLUDEPATH += /opt/Qt/5.15.2/gcc_64/include/QtCharts
INCLUDEPATH += ./include
CONFIG += qt debug
QT += widgets 
QT += charts

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
SOURCES += src/main.cpp src/stream_of_event.cpp
HEADERS += include/stream_of_event.h
# Output
DESTDIR = bin
