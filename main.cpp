#include <QApplication>
#include <QImage>
#include <QVector>
#include <QDebug>

#include "dandelion.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
#if defined(_WIN32)
    QString infile("F:\\data\\test\\timg.jpg");
    QString outfile("F:\\data\\test\\timg2.jpg");
#elif defined(__APPLE__)
    
#endif
    
#if 1
    PlotView view;
    view.show();
#endif
    
#if 0
    TImageRGB image(infile);
    qDebug() << image.width() << ", " << image.height();
    
    image.saveToFile(outfile);
    qDebug() << "finished...";
#endif
    
#if 0
    QImage img;
    img.load("F:\\data\\test\\timg.jpg");
    TImageView view;
    view.setMode(TImageView::MODE_ZOOM);
    view.setImage(img);
    view.show();
#endif
    
#if 0
    BasicGLView view;
    view.show();
#endif
    
#if 0
    ImageProcess1 win;
    win.show();
#endif
    
    return a.exec();
}
