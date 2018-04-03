#ifndef QTSURFACEPLOTTERRIBIDIALOG_H
#define QTSURFACEPLOTTERRIBIDIALOG_H

#include <QDialog>

namespace Ui {
  class QtSurfacePlotterRibiDialog;
}

namespace ribi {

class QtSurfacePlotterRibiDialog : public QDialog
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
