#ifndef BASICGLVIEW_H
#define BASICGLVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

/*
 * TODO: Everything!
 */

class BasicGLView : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    BasicGLView(QWidget* parent = 0);
    
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

};

#endif // BASICGLVIEW_H
