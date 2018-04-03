#ifndef QTSURFACEPLOTTERMENUDIALOG_H
#define QTSURFACEPLOTTERMENUDIALOG_H

#include <QDialog>

namespace Ui {
  class QtSurfacePlotterMenuDialog;
}

namespace ribi {

class QtSurfacePlotterMenuDialog : public QDialog
{
    Q_OBJECT //!OCLINT
    
public:
  explicit QtSurfacePlotterMenuDialog(QWidget *parent = 0);
  QtSurfacePlotterMenuDialog(const QtSurfacePlotterMenuDialog&) = delete;
  QtSurfacePlotterMenuDialog& operator=(const QtSurfacePlotterMenuDialog&) = delete;
  ~QtSurfacePlotterMenuDialog() noexcept;
    
private slots:
  void on_button_quit_clicked();
  void on_button_qwt_clicked();
  void on_button_ribi_clicked();

private:
  Ui::QtSurfacePlotterMenuDialog *ui;
};

} //~namespace ribi

#endif // QTSURFACEPLOTTERMENUDIALOG_H
