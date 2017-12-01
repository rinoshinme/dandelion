#include <QApplication>
#include <QImage>
#include <QVector>

#include "dandelion.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
#if 0
    // MainWindow w;
    // w.show();
    QImage image;
    image.load("F:\\data\\test\\timg.jpg");
    
    ImageView view;
    view.setImage(image);
    view.adjustImageFullWindow();
    view.show();
#else
    WaveView view;
    view.show();
    
#endif
    
    return a.exec();
}

