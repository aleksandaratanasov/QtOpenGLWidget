QtOpenGLWidget offers a start-up project for further development of 
applications that use the QGLWidget, part of the Qt framework. I use this for my 
terrain generator application (currently under development). I decide to separate 
the OpenGL widget's basic functionalities that I have implemented so that others 
can use it without the overhead of the rest of my application.

The widget consists of a top-level widget that also includes some controls and 
an embedded QGLWidget for viewing a 3D scene.

The project offers following features:

* OpenGL integration
* Basic navigation inside the OpenGL scene using a combination of Qt mouse 
event for rotation, translation and zooming
* Basic navigation and control outside the widget using buttons and a combobox

You can edit the project file to build either the shared library or the application
