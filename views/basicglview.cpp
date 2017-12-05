#include "basicglview.h"

BasicGLView::BasicGLView(QWidget* parent)
    :QOpenGLWidget(parent)
{
    
}

void BasicGLView::initializeGL()
{
    initializeOpenGLFunctions();
    setGeometry(300, 300, 500, 500);
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void BasicGLView::resizeGL(int w, int h)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void BasicGLView::paintGL()
{
}
