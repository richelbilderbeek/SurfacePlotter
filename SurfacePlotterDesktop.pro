# Fparser does not work with -Weffc++
CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14

#Specific, desktop
include(SurfacePlotterDesktop.pri)
include(QtSurfacePlotWidget.pri)

include(../RibiLibraries/Apfloat.pri)
include(../RibiLibraries/Fparser.pri)

# Qwt
LIBS += -lqwt-qt5

SOURCES += qtmain.cpp

# QResources give this error
QMAKE_CXXFLAGS += -Wno-unused-variable
