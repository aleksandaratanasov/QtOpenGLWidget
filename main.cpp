#include "qtopenglwidget.hpp"
#include <QApplication>

// Warning: it is generally a bad idea to mix GLUT with OpenGL
// Some functions (for example glutTeapot()) require a valid window session initialized by
// calling glutInit() which might cause problems because of the way both Qt and GLUT work
// In the current version of the widget on
int main(int argc, char *argv[])
{
  //glutInit(&argc, argv);
  QApplication a(argc, argv);
  QtOpenGLWidget w;
  w.show();

  return a.exec();
}
