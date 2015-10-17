#include <QMouseEvent>
#include <QString>
//#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>
#include "openglcontainer.hpp"

// Help methods and data structures
static void normalizeAngle(double &angle)
{
  while (angle < 0.) angle += 360. * 16;
  while (angle > 360.) angle -= 360. * 16;
}

struct point {
  GLfloat x;
  GLfloat y;
};

OpenGLContainer::OpenGLContainer(QWidget *parent) :
  QGLWidget(parent)
{
  viewMode = 0;
  xRot= 0.; yRot= 0.; zRot= 0.;
  xTrans= 0.; yTrans= 0.; zZoom = -2.;
  toggleTranslation = false;
}

void OpenGLContainer::initializeGL() {
  initializeGLFunctions();  // It is very important that initializeGLFunctions() is at this location in the code
  glClearColor(.2, .2, .2, 1);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHTING);  // requires glMaterial for the rendered objects to be viewed in color
  glEnable(GL_AUTO_NORMAL);
  glEnable(GL_NORMALIZE);
}

void OpenGLContainer::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  glTranslatef(xTrans, yTrans, zZoom);
  glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
  glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
  glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

  GLfloat light0_diffuse[] = {2.0, 0.0, 0.0, 1.0};
  GLfloat light0_position[] = {-2.0, 0.0, 2.0, 0.0};
  GLfloat light1_diffuse[] = {0.0, 0.0, 2.0, 1.0};
  GLfloat light1_position[] = {2.0, 0.0, 2.0, 0.0};

  // Sample content
  glPushMatrix();
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);;

    GLfloat material_ambient[] = {0.25f, 0.25f, 0.25f};
    GLfloat material_diffuse[] = {0.4f, 0.4f, 0.4f};
    GLfloat material_specular[] = {0.774597f, 0.774597f, 0.774597f};
    GLfloat material_shininess = 76.8f;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_shininess);

    //glutSolidSphere(1., 300, 300); // REQUIRED glutInit()!

    float f[] = {0, 2, -4, 1, 0, 0,
                 -2, -2, -4, 0, 1, 0,
                 2, -2, -4, 0, 0, 1
                };
      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_COLOR_ARRAY);
      // 3 (3 elements per vertex), GL_FLOAT (type of each element in each vertex),
      // 3 (stride - byte data between each vertex; here each we alternate between (vertex:3) and (color:3)),

      glVertexPointer(3, GL_FLOAT, 6*sizeof(float), f);
      glColorPointer(3, GL_FLOAT, 6*sizeof(float), &f[3]);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      glDisableClientState(GL_COLOR_ARRAY);
      glDisableClientState(GL_VERTEX_ARRAY);
  glPopMatrix();
}

void OpenGLContainer::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, (float)w/h, .01, 100.);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 0, 5,
            0, 0, 0,
            0, 1, 0);
}

void OpenGLContainer::changeViewMode(int mode) {
  viewMode = mode;
  switch (mode) {
    case 0:
      glDisable(GL_CULL_FACE);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      std::cout << "View mode set to solid" << std::endl;
      break;
    case 1:
      glEnable(GL_CULL_FACE);
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      std::cout << "View mode set to wireframe (with back culling)" << std::endl;
      break;
    case 2:
      glDisable(GL_CULL_FACE);
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
      std::cout << "View mode set to dots" << std::endl;
  }
  updateGL();
}

void OpenGLContainer::mousePressEvent(QMouseEvent *event) {
  lastPos = event->pos();

  if(event->buttons() & Qt::MiddleButton) toggleTranslation = true;
  else toggleTranslation = false;
}

void OpenGLContainer::mouseMoveEvent(QMouseEvent *event) {
  // Size of dx and dy represent the speed of movement along the respective axis
  int dx = event->x() - lastPos.x();
  int dy = event->y() - lastPos.y();

  if(event->buttons() & Qt::LeftButton) {
    setXRotation(xRot + 8. * dy);
    setYRotation(yRot + 8. * dx);
  }
  else if (event->buttons() & Qt::RightButton) {
    setXRotation(xRot + 8. * dy);
    setZRotation(zRot + 8. * dx);
  }

  lastPos = event->pos();

  // Translate camera horizontally and vertically
  if(toggleTranslation) setXYTranslation(dx, dy);
}

void OpenGLContainer::wheelEvent(QWheelEvent *event) {
  int numDegrees = event->delta() / 8;
  int numSteps = numDegrees / 15; // Usually numSteps here is declared outside the function and is used for tracking the number of steps
                                  // the wheel has been rolled. However here we use it only to determine the direction of the scroll of the wheel

  // TODO After the settings dialog is added make the zoom factor changable
  if(numSteps == 1) zZoom += .01;
  else if (numSteps == -1) zZoom -= .01;

  setZoom(numSteps);

  /*if((event->buttons() & Qt::MiddleButton) != 0) {
    std::cout << "MouseWheelEven: wheel pressed" << std::endl;
  }*/
}

void OpenGLContainer::setXRotation(double angle)
{
  normalizeAngle(angle);
  if (angle != xRot) {
    xRot = angle;
    emit xRotationChanged(angle);
    updateGL();
  }
}

void OpenGLContainer::setYRotation(double angle)
{
  normalizeAngle(angle);
  if (angle != yRot) {
    yRot = angle;
    emit yRotationChanged(angle);
    updateGL();
  }
}

void OpenGLContainer::setZRotation(double angle)
{
  normalizeAngle(angle);
  if (angle != zRot) {
    zRot = angle;
    emit zRotationChanged(angle);
    updateGL();
  }
}

void OpenGLContainer::setXYTranslation(int speedX, int speedY)
{
  // Covers both positive and negative values for y
  // TODO After the settings dialog is added make the defaul translation factor (here: .01) changable
  // I've noticed that the more zoomed out the scene is the less noticable the translation is if I use a constant factor
  // (here: .01). However if I combine this factor with the zoom level the translation speed gradually increases the more
  // zoomed out the scene is (and decreases upon zoom in), which leads to a very nice adaptive navigation
  xTrans += .01 * speedX * zZoom;
  // The multiplication with -1 inverts the movement so that moving the mouse cursor upwards translates upwards
  yTrans += .01 * speedY * zZoom * (-1);
  std::cout << "(x: " << QString::number(xTrans, 'g', 3).toUtf8().constData() << "; y: " << QString::number(yTrans, 'g', 3).toUtf8().constData() << ")" << std::endl;
  emit xTranslationChanged(xTrans);
  emit yTranslationChanged(yTrans);
  updateGL();
}

void OpenGLContainer::setZoom(int zoomDirection) {
  // We increase the Z distance (the axis which points outwards the scene in the direction of the user)
  // based on the direction
  if(zoomDirection == 1) zoomIn();
  else if (zoomDirection == -1) zoomOut();
}

void OpenGLContainer::zoomIn() {
  zZoom += .1;
  std::cout << "Zoom in to " << QString::number(zZoom, 'g', 3).toUtf8().constData() << std::endl;
  emit zTranslationChanged(zZoom);
  updateGL();
}

void OpenGLContainer::zoomOut() {
  zZoom -= .1;
  std::cout << "Zoom out to " << QString::number(zZoom, 'g', 3).toUtf8().constData() << std::endl;
  emit zTranslationChanged(zZoom);
  updateGL();
}

void OpenGLContainer::zoomReset() {
  zZoom = -2.0;
  std::cout << "Zoom level reset to " << QString::number(zZoom, 'g', 3).toUtf8().constData() << std::endl;
  updateGL();
}

void OpenGLContainer::resetRotation() {
  xRot = yRot = zRot = 0.;
  std::cout << "Rotation reset" << std::endl;
  updateGL();
}

void OpenGLContainer::resetTranslation() {
  xTrans = 0.;
  yTrans = 0.;
  std::cout << "Translation reset to (x: " << QString::number(xTrans, 'g', 3).toUtf8().constData() << "; y: " << QString::number(yTrans, 'g', 3).toUtf8().constData() << ")" << std::endl;
  updateGL();
}
