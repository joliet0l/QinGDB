include(../QinGDB.pri)


QT += core gui widgets

HEADERS = \
    mainwindow.h \
    editortoolbar.h
SOURCES = \
    main.cpp \
    mainwindow.cpp \
    editortoolbar.cpp

TARGET = QinGDB 

LIBS += -lutils -lqscintilla2



	
#! [0]
RESOURCES = QinGDB.qrc
#! [0]
RC_ICONS = QinGDB.ico
RC_FILE = QinGDB.rc


