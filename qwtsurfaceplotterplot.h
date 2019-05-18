#ifndef RIBI_QWTSURFACEPLOTTERPLOT_H
#define RIBI_QWTSURFACEPLOTTERPLOT_H

#include <memory>
#include <qwt/qwt_plot.h>

struct FunctionParser;
struct QwtLinearColorMap;
struct QwtPlotSpectrogram;

namespace ribi {

struct QwtSurfacePlotterData;
struct QwtSurfacePlotterZoomer;

class QwtSurfacePlotterPlot: public QwtPlot
{
    Q_OBJECT //!OCLINT

public:
  QwtSurfacePlotterPlot(QWidget * parent = nullptr);
  QwtSurfacePlotterPlot(const QwtSurfacePlotterPlot&) = delete;
  QwtSurfacePlotterPlot& operator=(const QwtSurfacePlotterPlot&) = delete;

public slots:
  void SetData(
    const std::shared_ptr<FunctionParser>& function_parser,
    const double minx, const double maxx,
    const double miny, const double maxy,
    const double minz, const double maxz
  );
  void SetData(
    const std::string& function_str,
    const double minx, const double maxx,
    const double miny, const double maxy,
    const double minz, const double maxz
  );
  void showContour(bool do_show);
  void showSpectrogram(bool do_show);

private:
  QwtPlotSpectrogram * const m_spectrogram;

};

QwtLinearColorMap * CreateColorMap() noexcept;

} //~namespace ribi

#endif // RIBI_QWTSURFACEPLOTTERPLOT_H
