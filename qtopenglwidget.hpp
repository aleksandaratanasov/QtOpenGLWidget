#ifndef QTOPENGLWIDGET_HPP
#define QTOPENGLWIDGET_HPP

#include <QWidget>

namespace Ui {
  class QtOpenGLWidget;
}

class QtOpenGLWidget : public QWidget
{
    Q_OBJECT

  public:
    explicit QtOpenGLWidget(QWidget *parent = 0);
    ~QtOpenGLWidget();

  private:
    Ui::QtOpenGLWidget *ui;
};

#endif // QTOPENGLWIDGET_HPP
