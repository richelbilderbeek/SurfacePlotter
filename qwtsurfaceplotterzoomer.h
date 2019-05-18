#ifndef RIBI_QWTSURFACEPLOTTERZOOMER_H
#define RIBI_QWTSURFACEPLOTTERZOOMER_H

#include <qwt/qwt_plot_zoomer.h>

namespace ribi {

struct QwtSurfacePlotterZoomer: public QwtPlotZoomer
{
  QwtSurfacePlotterZoomer(QWidget * const canvas);
  QwtText trackerTextF(const QPointF &pos) const;
};

} //~namespace ribi

#endif // RIBI_QWTSURFACEPLOTTERZOOMER_H
