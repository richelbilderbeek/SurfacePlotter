#ifndef QTSURFACEPLOTTERQWTDIALOG_H
#define QTSURFACEPLOTTERQWTDIALOG_H

#include <QDialog>

namespace Ui {
  class QtSurfacePlotterQwtDialog;
}

namespace ribi {

struct QwtSurfacePlotterPlot;

class QtSurfacePlotterQwtDialog : public QDialog
{
  Q_OBJECT //!OCLINT
    
public:
  explicit QtSurfacePlotterQwtDialog(QWidget *parent = 0);
  QtSurfacePlotterQwtDialog(const QtSurfacePlotterQwtDialog&) = delete;
  QtSurfacePlotterQwtDialog& operator=(const QtSurfacePlotterQwtDialog&) = delete;
  ~QtSurfacePlotterQwtDialog() noexcept;
    
private slots:
  void keyPressEvent(QKeyEvent *event);
  void OnAnyChange();

private:
  Ui::QtSurfacePlotterQwtDialog *ui;
  QwtSurfacePlotterPlot * const m_plot;
};

} //~namespace ribi

#endif // QTSURFACEPLOTTERQWTDIALOG_H
