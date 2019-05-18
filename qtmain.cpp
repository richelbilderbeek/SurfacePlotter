#include <QApplication>
#include "qtsurfaceplottermenudialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::QtSurfacePlotterMenuDialog w;
  w.show();
  return a.exec();
}
