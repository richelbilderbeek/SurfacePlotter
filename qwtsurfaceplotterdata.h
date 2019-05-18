#ifndef RIBI_QWTSURFACEPLOTTERDATA_H
#define RIBI_QWTSURFACEPLOTTERDATA_H

#include <memory>

#include <qwt/qwt_matrix_raster_data.h>

struct FunctionParser;

namespace ribi {

///The spectrogram data
struct QwtSurfacePlotterData: public QwtRasterData
{
  QwtSurfacePlotterData(
    const std::shared_ptr<FunctionParser>& function_parser,
    const double minx = -1.0, const double maxx = 1.0,
    const double miny = -1.0, const double maxy = 1.0,
    const double minz = -1.0, const double maxz = 1.0

  );
  double value(const double x, const double y) const noexcept;

  private:
  const std::shared_ptr<FunctionParser> m_function_parser;
};

} //~namespace ribi

#endif // RIBI_QWTSURFACEPLOTTERDATA_H
