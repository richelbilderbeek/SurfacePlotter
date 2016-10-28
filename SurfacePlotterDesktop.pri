include(SurfacePlotterConsole.pri)

SOURCES += \
    $$PWD/qtsurfaceplottermenudialog.cpp \
    $$PWD/qtsurfaceplotterqwtdialog.cpp \
    $$PWD/qtsurfaceplotterribidialog.cpp \
    $$PWD/qwtsurfaceplotterzoomer.cpp \
    $$PWD/qwtsurfaceplotterplot.cpp \
    $$PWD/qwtsurfaceplotterdata.cpp

FORMS += \
    $$PWD/qtsurfaceplottermenudialog.ui \
    $$PWD/qtsurfaceplotterqwtdialog.ui \
    $$PWD/qtsurfaceplotterribidialog.ui

HEADERS += \
    $$PWD/qtsurfaceplottermenudialog.h \
    $$PWD/qtsurfaceplotterqwtdialog.h \
    $$PWD/qtsurfaceplotterribidialog.h \
    $$PWD/qwtsurfaceplotterzoomer.h \
    $$PWD/qwtsurfaceplotterplot.h \
    $$PWD/qwtsurfaceplotterdata.h
