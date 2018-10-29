TEMPLATE = app
QT += widgets webenginewidgets network
TARGET = ubt
DEPENDPATH += .
INCLUDEPATH += .
LIBS += -lsqlite3
FORMS += \
    mainwindow.ui

HEADERS += \
    ytb_viewer.h \
    mainwindow.h \
    database.h \
    song.h

SOURCES += \
    main.cpp \
    ytb_viewer.cpp \
    mainwindow.cpp \
    database.cpp \
    song.cpp
