#include <QStringList>
#include <QAction>
#include "qtopenglwidget.hpp"
#include "ui_qtopenglwidget.h"

QtOpenGLWidget::QtOpenGLWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtOpenGLWidget)
{
  ui->setupUi(this);
  QStringList polygoneModes;
  polygoneModes.append("fill");
  polygoneModes.append("wireframe (back cull)");
  polygoneModes.append("dots");
  ui->comboBoxViewModes->addItems(polygoneModes);
  ui->comboBoxViewModes->setCurrentIndex(0);

  QAction *quitShortcut = new QAction(this);
  quitShortcut->setShortcut(Qt::Key_Q | Qt::CTRL);
  connect(quitShortcut, SIGNAL(triggered()), this, SLOT(close()));
  this->addAction(quitShortcut);
}

QtOpenGLWidget::~QtOpenGLWidget()
{
  delete ui;
}
