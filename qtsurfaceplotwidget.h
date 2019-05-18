#ifndef QTSURFACEPLOTWIDGET_H
#define QTSURFACEPLOTWIDGET_H

#include <string>
#include <vector>
#include <QWidget>

namespace ribi {

struct QtSurfacePlotWidget : public QWidget
{
  Q_OBJECT
public:

  explicit QtSurfacePlotWidget(QWidget *parent = 0);

  ///A functor to do the plotting
  struct Function
  {
    virtual ~Function() noexcept {}
    virtual double operator()(const double x, const double y) const noexcept = 0;
  };

  ///Plot a function for a certain range
  void Plot(
    const Function& f,
    const double x_min, const double x_max,
    const double y_min, const double y_max
  ) noexcept;

  ///Sets the image of the surface plot to the values of the vector
  ///The doubles can be in any range
  void SetSurfaceGrey(const std::vector<std::vector<double>>& surface);

  ///Sets the image of the surface plot to the values of the vector
  ///Assumes that the chars are in the range [0,255] (a char's range)
  ///If the chars are in a shorter range, they will NOT be rescaled to [0,255]
  void SetSurfaceGrey(const std::vector<std::vector<unsigned char>>& surface);

protected:
  void paintEvent(QPaintEvent *) override;
  void resizeEvent(QResizeEvent *) override;

private:
  std::vector<std::vector<unsigned char>> m_surface;

  ///Rescale calculates a value between old_min and old_max its relative place and transforms
  ///this relative position to a new_min and new_max
  ///For example: for the old range [1,5], the value 2 is at 25% of this range. Transforming this
  ///to the new range range [0,100] results in a 25
  static double Rescale(
    const double value,
    const double old_min,
    const double old_max,
    const double new_min,
    const double new_max
  ) noexcept;
};

///Rescale calculates a value between old_min and old_max its relative place and transforms
///this relative position to a new_min and new_max
///For example: for the old range [1,5], the value 2 is at 25% of this range. Transforming this
///to the new range range [0,100] results in a 25
double Rescale(
  const double value,
  const double old_min,
  const double old_max,
  const double new_min,
  const double new_max
) noexcept;

} //~namespace ribi

#endif //QTSURFACEPLOTWIDGET_H
