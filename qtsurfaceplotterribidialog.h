//---------------------------------------------------------------------------
/*
SurfacePlotter, plots a bivariate function
Copyright (C) 2010-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/SurfacePlotter.htm
//---------------------------------------------------------------------------
#ifndef QTSURFACEPLOTTERRIBIDIALOG_H
#define QTSURFACEPLOTTERRIBIDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtSurfacePlotterRibiDialog;
}

namespace ribi {

class QtSurfacePlotterRibiDialog : public QtHideAndShowDialog
{
  Q_OBJECT //!OCLINT
    
public:
  explicit QtSurfacePlotterRibiDialog(QWidget *parent = 0);
  QtSurfacePlotterRibiDialog(const QtSurfacePlotterRibiDialog&) = delete;
  QtSurfacePlotterRibiDialog& operator=(const QtSurfacePlotterRibiDialog&) = delete;
  ~QtSurfacePlotterRibiDialog() noexcept;
    
private slots:
  void keyPressEvent(QKeyEvent *event);
  void OnAnyChange();
  void resizeEvent(QResizeEvent *);

private:
  Ui::QtSurfacePlotterRibiDialog *ui;
};

} //~namespace ribi

#endif // QTSURFACEPLOTTERRIBIDIALOG_H
