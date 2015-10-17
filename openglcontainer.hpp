#ifndef OPENGLCONTAINER_HPP
#define OPENGLCONTAINER_HPP

#include <QWidget>
#include <QGLFunctions>
#include <QPoint>

// The control for the OpenGL widget was insipred by http://www.bogotobogo.com/Qt/Qt5_OpenGL_QGLWidget.php

class OpenGLContainer : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT

  private:
    int viewMode;
    double xRot;
    double yRot;
    double zRot;
    QPoint lastPos;
    double xTrans;
    double yTrans;
    double zZoom;  // zTrans
    bool toggleTranslation;

  public:
    explicit OpenGLContainer(QWidget *parent = 0);

  private:
    /**
     * @brief initializeGL initializes the OpenGL environment
     */
    void initializeGL();
    /**
     * @brief paintGL triggered when redrawing is required (updageGL() or update(); for example: resizing, hiding etc. the widget)
     */
    void paintGL();
    /**
     * @brief resizeGL triggered when resizing the widget (also triggers paintGL())
     * @param w new width of the widget
     * @param h new height of the widget
     */
    void resizeGL(int w, int h);
    /**
     * @brief mousePressEvent handles the pressing of mouse buttons incl. the mouse wheel
     * @param event gives information about which mouse button has been pressed
     */
    void mousePressEvent(QMouseEvent *event);
    /**
     * @brief mouseMoveEvent handles the movement of the mouse (coordinates of the cursor)
     * @param event gives information about the mouse movement (used for the translation along the X and Y axes and rotation around all three axes)
     */
    void mouseMoveEvent(QMouseEvent *event);
    /**
     * @brief wheelEvent handles the scrolling of the mouse wheel
     * @param event gives information about the rotation of the mouse wheel (used for the translation along the X and Y axes and rotation around all three axes)
     */
    void wheelEvent(QWheelEvent *event);
    // Rotation
    /**
     * @brief setXRotation
     * @param angle changed value for the rotation angle around the X axis (used for the translation along the Z axis)
     */
    void setXRotation(double angle);
    /**
     * @brief setYRotation
     * @param angle changed value for the rotation angle around the Y axis
     */
    void setYRotation(double angle);
    /**
     * @brief setZRotation
     * @param angle changed value for the rotation angle around the Z axis
     */
    void setZRotation(double angle);
    // Translation
    /**
     * @brief setXYTranslation translates the camera along the X and Y axes using mouse input (left button + drag)
     * @param speedX the speed of the mouse cursor along the X axis
     * @param speedY the speed of the mouse cursor along the Y axis
     */
    void setXYTranslation(int speedX, int speedY);     // Up/Down and Left/Right
    /**
     * @brief setZoom translates the camera along the Z axis using mouse input (wheel)
     * @param zoomDirection
     */
    void setZoom(int zoomDirection);      // Nearer/Closer to viewer

  public slots:
    /**
     * @brief changeViewMode changes the polygon mode that is used
     * @param mode (0 : solid, 1 : wireframe)
     */
    void changeViewMode(int mode);
    /**
     * @brief resetZoom resets the translation along the Z axis to its initial value of -2.0
     */
    void zoomReset();
    /**
     * @brief zoomIn translates the camera long the Z axis toward the scene (same as scrolling up with the mouse wheel)
     */
    void zoomIn();
    /**
     * @brief zoomOut translates the camera long the Z axis outward the scene (same as scrolling down with the mouse wheel)
     */
    void zoomOut();
    /**
     * @brief resetTranslation resets the translation along the X and Y axes to their initial values of 1.0
     */
    void resetTranslation();
    /**
     * @brief resetRotation resets the rotation around the X, Y and Z axes to their initial values of 1.0
     */
    void resetRotation();

  signals:  // Following signals can be used to externally detect changes that happen inside the widget
    // Rotate around x, y and z axes using mouse
    void xRotationChanged(double angle);
    void yRotationChanged(double angle);
    void zRotationChanged(double angle);
    // Translate along x, y and z (zoom) axes using the mouse
    void xTranslationChanged(double x);
    void yTranslationChanged(double y);
    void zTranslationChanged(double z);
};

#endif // OPENGLCONTAINER_HPP
