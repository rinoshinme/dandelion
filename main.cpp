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
    double arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    HistView view;
    view.setValues(arr, 10);
    view.show();
    
#endif
    
    return a.exec();
}

