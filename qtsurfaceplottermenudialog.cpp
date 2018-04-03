#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtsurfaceplotwidget.h"
#include "surfaceplottermenudialog.h"
#include "qtsurfaceplotterqwtdialog.h"
#include "qtsurfaceplotterribidialog.h"
#include "qtsurfaceplottermenudialog.h"
#include "ui_qtsurfaceplottermenudialog.h"
#pragma GCC diagnostic pop

ribi::QtSurfacePlotterMenuDialog::QtSurfacePlotterMenuDialog(QWidget *parent)
  : QDialog(parent),
    ui(new Ui::QtSurfacePlotterMenuDialog)
{
  ui->setupUi(this);
}

ribi::QtSurfacePlotterMenuDialog::~QtSurfacePlotterMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtSurfacePlotterMenuDialog::on_button_quit_clicked()
{
  this->close();
}

void ribi::QtSurfacePlotterMenuDialog::on_button_qwt_clicked()
{
  QtSurfacePlotterQwtDialog d;
  d.setStyleSheet(this->styleSheet());
  d.exec();
}

void ribi::QtSurfacePlotterMenuDialog::on_button_ribi_clicked()
{
  QtSurfacePlotterRibiDialog d;
  d.setStyleSheet(this->styleSheet());
  d.exec();
}
