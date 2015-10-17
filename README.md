QtOpenGLWidget offers a start-up project for further development of 
applications that use the QGLWidget, part of the Qt framework. I use this for my 
terrain generator application (currently under development). I decide to separate 
the OpenGL widget's basic functionalities that I have implemented so that others 
can use it without the overhead of the rest of my application.

* OpenGL integration
* Basic navigation inside the OpenGL scene using a combination of Qt mouse 
event for rotation, translation and zooming
* Basic navigation and control outside the widget using buttons and a combobox

###TODO###
Conver the project to a shared library so that it can be easily integrated into 
other projects
