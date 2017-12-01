#include <QApplication>
#include <QImage>
#include <QVector>
#include <QDebug>

#include "dandelion.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    QString infile("F:\\data\\test\\timg.jpg");
    QString outfile("F:\\data\\test\\timg2.jpg");
    
    /*
    TImageRGB image(infile);
    qDebug() << image.width() << ", " << image.height();
    
    image.saveToFile(outfile);
    qDebug() << "finished...";
    */
    
    QImage img;
    img.load("F:\\data\\test\\timg.jpg");
    TImageView view;
    view.setMode(TImageView::MODE_ZOOM);
    view.setImage(img);
    view.show();
    
    // ImageProcess1 win;
    // win.show();
    
    return a.exec();
}
