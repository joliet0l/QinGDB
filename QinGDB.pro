QT += widgets

INCLUDEPATH += $$PWD/include/QScintilla

HEADERS = \
    mainwindow.h \
    styledbar.h \
    editortoolbar.h
SOURCES = \
    main.cpp \
    mainwindow.cpp \
    styledbar.cpp \
    editortoolbar.cpp
	
LIBS += -L. -lqscintilla2


#! [0]
RESOURCES     = QinGDB.qrc
#! [0]
RC_ICONS = QinGDB.ico
RC_FILE = QinGDB.rc
