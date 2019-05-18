#include "qwtsurfaceplotterzoomer.h"

#include <qwt/qwt_plot_canvas.h>

ribi::QwtSurfacePlotterZoomer::QwtSurfacePlotterZoomer(QWidget * const canvas)
  : QwtPlotZoomer(dynamic_cast<QwtPlotCanvas *>(canvas))
{
  setTrackerMode(AlwaysOn);
}

QwtText ribi::QwtSurfacePlotterZoomer::trackerTextF(const QPointF& pos) const
{
  const QColor bg(255,255,255,200); //  Qt::white,);
  //bg.setAlpha( 200 );

  QwtText text = QwtPlotZoomer::trackerTextF( pos );
  text.setBackgroundBrush(QBrush(bg));
  return text;
}
