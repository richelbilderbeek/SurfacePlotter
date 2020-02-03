#include <algorithm>
#include <cassert>
#include <vector>

#include <QPainter>

#include "qtsurfaceplotwidget.h"

ribi::QtSurfacePlotWidget::QtSurfacePlotWidget(QWidget *parent)
  : QWidget(parent),
    m_surface{}
{
  #ifndef NDEBUG
  assert(Rescale(2.0,1.0,5.0,0.0,100.0) >= 24.9999 && Rescale(2.0,1.0,5.0,0.0,100.0) < 25.0001);
  #endif

  std::vector<std::vector<unsigned char>> v(128,std::vector<unsigned char>(128));
  for(int y=0; y!=128; ++y)
  {
    for (int x=0; x!=128; ++x)
    {
      v[y][x] = x + y;
    }
  }
  SetSurfaceGrey(v);
}

void ribi::QtSurfacePlotWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  assert(!m_surface.empty());
  const int maxy = m_surface.size();
  assert(maxy > 0);
  const int maxx = m_surface[0].size();
  assert(maxx > 0);
  QImage image (maxx,maxy,QImage::Format::Format_RGB32);

  for (int y=0; y!=maxy; ++y)
  {
    std::vector<unsigned char>& line = m_surface[y];
    for (int x=0; x!=maxx; ++x)
    {
      assert(x < static_cast<int>(line.size()));
      const unsigned char grey = line[x];
      image.setPixel(x,y,qRgb(grey,grey,grey));
    }
  }
  painter.drawPixmap(0,0,this->width(),this->height(),QPixmap::fromImage(image));

}


void ribi::QtSurfacePlotWidget::Plot(
  const Function& f,
  const double x_min, const double x_max,
  const double y_min, const double y_max
) noexcept
{
  assert(x_min < x_max);
  assert(y_min < y_max);
  //Evaluate the function in a 2D std::vector
  const int n_rows = height();
  const int n_cols = width();
  std::vector<std::vector<double>> v(n_rows,std::vector<double>(n_cols,0.0));
  const double n_rows_d = static_cast<double>(n_rows);
  const double n_cols_d = static_cast<double>(n_cols);

  for (int y = 0; y!=n_rows; ++y)
  {
    const double yD = static_cast<double>(y);
    const double y_scaled = Rescale(yD,0.0,n_rows_d,y_min,y_max);
    for (int x = 0; x!=n_cols; ++x)
    {
      const double xD = static_cast<double>(x);
      const double x_scaled = Rescale(xD,0.0,n_cols_d,x_min,x_max);
      const double z = f(x_scaled,y_scaled);
      v[y][x] = z;
    }
  }
  //Plot the 2D std::vector
  SetSurfaceGrey(v);
}

double ribi::QtSurfacePlotWidget::Rescale(
  const double value,
  const double old_min,
  const double old_max,
  const double new_min,
  const double new_max) noexcept
{
  return ribi::Rescale(value, old_min, old_max, new_min, new_max);
}

double ribi::Rescale(
  const double value,
  const double old_min,
  const double old_max,
  const double new_min,
  const double new_max) noexcept
{
  assert(value >= old_min);
  assert(value <= old_max);
  const double old_distance = old_max - old_min;
  //At which relative distance is value on old_min to old_max ?
  const double distance = (value - old_min) / old_distance;
  assert(distance >= 0.0);
  assert(distance <= 1.0);
  const double new_distance = new_max - new_min;
  const double new_value = new_min + (distance * new_distance);
  assert(new_value >= new_min);
  assert(new_value <= new_max);
  return new_value;
}

void ribi::QtSurfacePlotWidget::resizeEvent(QResizeEvent *)
{
  this->repaint();
}

void ribi::QtSurfacePlotWidget::SetSurfaceGrey(const std::vector<std::vector<double>>& v)
{
  //Get the size
  assert(!v.empty());
  const int maxx = v[0].size();
  const int maxy = v.size();
  //Minimum and maximum are not given, so these need to be calculated
  double min_val = *(std::min_element(v[0].begin(),v[0].end()));
  double max_val = *(std::max_element(v[0].begin(),v[0].end()));
  for (int y=1; y!=maxy; ++y) //1, because 0 gets know the lines above
  {
    const double local_min_val = *(std::min_element(v[y].begin(),v[y].end()));
    const double local_max_val = *(std::max_element(v[y].begin(),v[y].end()));
    if (local_min_val < min_val) min_val = local_min_val;
    if (local_max_val > max_val) max_val = local_max_val;
  }
  //Create a black surface of type unsigned char
  std::vector<std::vector<unsigned char>> w(maxy,std::vector<unsigned char>(maxx,0));
  if (min_val == max_val)
  {
    //Keep black surface in w black
  }
  else
  {
    for (int y=0; y!=maxy; ++y)
    {
      const std::vector<double>& line_in = v[y];
      std::vector<unsigned char>& line_out = w[y];
      for (int x=0; x!=maxx; ++x)
      {
        assert(min_val != max_val);
        assert(min_val < max_val);
        assert(x < static_cast<int>(line_in.size()));
        const double grey_double = (line_in[x] - min_val) / (max_val - min_val);
        assert(grey_double >= 0.0 && grey_double <= 1.0);
        const unsigned char grey = grey_double * 255.0;
        assert(x < static_cast<int>(line_out.size()));
        line_out[x] = grey;
      }
    }
  }
  SetSurfaceGrey(w);
}

void ribi::QtSurfacePlotWidget::SetSurfaceGrey(const std::vector<std::vector<unsigned char>>& surface)
{
  m_surface = surface;
  this->repaint();
}

