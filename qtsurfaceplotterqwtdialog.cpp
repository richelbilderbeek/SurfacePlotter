#include "qtsurfaceplotterqwtdialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>

#include <QDesktopWidget>
#include <QKeyEvent>

#include "fparser.hh"


#include "ui_qtsurfaceplotterqwtdialog.h"
#include "qwtsurfaceplotterplot.h"

ribi::QtSurfacePlotterQwtDialog::QtSurfacePlotterQwtDialog(QWidget *parent)
  : QDialog(parent),
    ui(new Ui::QtSurfacePlotterQwtDialog),
    m_plot(new QwtSurfacePlotterPlot(this))
{
  ui->setupUi(this);

  ui->edit_maxx->setValue( 1.0);
  ui->edit_maxy->setValue( 1.0);
  ui->edit_maxz->setValue( 1.0);
  ui->edit_minx->setValue(-1.0);
  ui->edit_miny->setValue(-1.0);
  ui->edit_minz->setValue(-1.0);

  ui->edit_equation->setText("cos(x*y*10)");

  {
    assert(!ui->widget->layout());
    QGridLayout * const my_layout = new QGridLayout;
    ui->widget->setLayout(my_layout);
    my_layout->addWidget(m_plot);
  }

  {
    //Put the dialog in the screen center at 50% x 50% of its size
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() / 2,screen.height() / 2);
    this->move( screen.center() - this->rect().center() );
  }

  QObject::connect(this->ui->edit_equation,SIGNAL(textChanged(QString)),this, SLOT(OnAnyChange()));
  QObject::connect(this->ui->edit_maxx,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->edit_maxy,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->edit_maxz,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->edit_minx,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->edit_miny,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->edit_minz,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));

  OnAnyChange();
  m_plot->showSpectrogram(true);
  m_plot->showContour(true);
}

ribi::QtSurfacePlotterQwtDialog::~QtSurfacePlotterQwtDialog() noexcept
{
  delete ui;
}

void ribi::QtSurfacePlotterQwtDialog::keyPressEvent(QKeyEvent * e)
{
  switch (e->key())
  {
    case Qt::Key_Up: m_plot->showSpectrogram(true); break;
    case Qt::Key_Down: m_plot->showSpectrogram(false); break;
    case Qt::Key_Right: m_plot->showContour(true); break;
    case Qt::Key_Left: m_plot->showContour(false); break;
    case Qt::Key_Escape: close(); return;
  }
}

void ribi::QtSurfacePlotterQwtDialog::OnAnyChange()
{
  const auto f = std::make_shared<FunctionParser>();

  //Parse the formula
  f->Parse(ui->edit_equation->text().toStdString().c_str(),"x,y");
  if (f->GetParseErrorType() != FunctionParser::FP_NO_ERROR)
  {
    this->setWindowTitle("Function cannot not be parsed"); return;
  }


  const double x_min = ui->edit_minx->value();
  const double y_min = ui->edit_miny->value();
  const double z_min = ui->edit_minz->value();
  const double x_max = ui->edit_maxx->value();
  const double y_max = ui->edit_maxy->value();
  const double z_max = ui->edit_maxz->value();


  if (x_min >= x_max)
  {
    this->setWindowTitle("Value of x_min must be smaller than x_max"); return;
  }

  if (y_min >= y_max)
  {
    this->setWindowTitle("Value of y_min must be smaller than y_max"); return;
  }

  if (z_min >= z_max)
  {
    this->setWindowTitle("Value of z_min must be smaller than z_max"); return;
  }

  m_plot->SetData(
    f,
    x_min,x_max,
    y_min,y_max,
    z_min,z_max
  );

  this->setWindowTitle("Function plotted successfully");
}
