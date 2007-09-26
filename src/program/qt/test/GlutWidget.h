#ifndef GLUT_WIDGET_H
#define GLUT_WIDGET_H

#include <glt/gl.h>
#include <QGLWidget>

class GlutWidget : public QGLWidget
{
    Q_OBJECT

public:
    GlutWidget(QWidget *parent = NULL);

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int width, int height);
};
 
#endif
