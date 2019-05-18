#include "qtsurfaceplotterribidialog.h"

#include <cassert>
#include <boost/lexical_cast.hpp>

#include <QDesktopWidget>
#include <QKeyEvent>
#include "fparser.hh"

#include "ui_qtsurfaceplotterribidialog.h"

ribi::QtSurfacePlotterRibiDialog::QtSurfacePlotterRibiDialog(QWidget *parent)
  : QDialog(parent),
    ui(new Ui::QtSurfacePlotterRibiDialog)
{
  ui->setupUi(this);

  QObject::connect(this->ui->edit_equation,SIGNAL(textChanged(QString)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->edit_minx,SIGNAL(textChanged(QString)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->edit_miny,SIGNAL(textChanged(QString)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->edit_maxx,SIGNAL(textChanged(QString)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->edit_maxy,SIGNAL(textChanged(QString)),this,SLOT(OnAnyChange()));


  ui->edit_minx->setText(boost::lexical_cast<std::string>(-1.0).c_str());
  ui->edit_miny->setText(boost::lexical_cast<std::string>(-1.0).c_str());
  ui->edit_maxx->setText(boost::lexical_cast<std::string>( 1.0).c_str());
  ui->edit_maxy->setText(boost::lexical_cast<std::string>( 1.0).c_str());

  ui->edit_equation->setText("cos(x*y*100)");

  {
    //Put the dialog in the screen center at 50% x 50% of its size
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() / 2,screen.height() / 2);
    this->move( screen.center() - this->rect().center() );
  }
}

ribi::QtSurfacePlotterRibiDialog::~QtSurfacePlotterRibiDialog() noexcept
{
  delete ui;
}

void ribi::QtSurfacePlotterRibiDialog::keyPressEvent(QKeyEvent *event)
{
 switch (event->key())
  {
    case Qt::Key_Escape: close(); return;
  }
}

void ribi::QtSurfacePlotterRibiDialog::OnAnyChange()
{
  try { boost::lexical_cast<double>(ui->edit_minx->text().toStdString()); }
  catch (boost::bad_lexical_cast&)
  {
    this->setWindowTitle("Value of x_min is not a valid double"); return;
  }
  try { boost::lexical_cast<double>(ui->edit_miny->text().toStdString()); }
  catch (boost::bad_lexical_cast&)
  {
    this->setWindowTitle("Value of y_min is not a valid double"); return;
  }
  try { boost::lexical_cast<double>(ui->edit_maxx->text().toStdString()); }
  catch (boost::bad_lexical_cast&)
  {
    this->setWindowTitle("Value of x_max is not a valid double"); return;
  }
  try { boost::lexical_cast<double>(ui->edit_maxy->text().toStdString()); }
  catch (boost::bad_lexical_cast&)
  {
    this->setWindowTitle("Value of y_max is not a valid double"); return;
  }

  FunctionParser f;

  //Parse the formula
  f.Parse(ui->edit_equation->text().toStdString().c_str(),"x,y");
  if (f.GetParseErrorType()!= FunctionParser::FP_NO_ERROR)
  {
    this->setWindowTitle("Function cannot not be parsed"); return;
  }


  const double x_min = boost::lexical_cast<double>(ui->edit_minx->text().toStdString());
  const double y_min = boost::lexical_cast<double>(ui->edit_miny->text().toStdString());
  const double x_max = boost::lexical_cast<double>(ui->edit_maxx->text().toStdString());
  const double y_max = boost::lexical_cast<double>(ui->edit_maxy->text().toStdString());

  if (x_min >= x_max)
  {
    this->setWindowTitle("Value of x_min must be smaller than x_max"); return;
  }

  if (y_min >= y_max)
  {
    this->setWindowTitle("Value of y_min must be smaller than y_max"); return;
  }

  struct MyFunction : public QtSurfacePlotWidget::Function
  {
    MyFunction(const FunctionParser& f) : m_f(f) {}
    double operator()(const double x, const double y) const noexcept
    {
      const double xs[2] = { x,y };
      //FunctionParser::Eval is not const, although it does not change
      //the state of the FunctionParser itself
      const double z{const_cast<FunctionParser&>(m_f).Eval(xs)};
      return m_f.EvalError() ? 0.0 : z;
    }
    private:
    const FunctionParser m_f;
  };

  ui->surfaceplotwidget->Plot(
    MyFunction(f),
    x_min, x_max,
    y_min, y_max
  );

  this->setWindowTitle("Function plotted successfully");

}

void ribi::QtSurfacePlotterRibiDialog::resizeEvent(QResizeEvent *)
{
  OnAnyChange();
}
