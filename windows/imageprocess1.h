#ifndef IMAGEPROCESS1_H
#define IMAGEPROCESS1_H

#include <QWidget>
#include "../views/timageview.h"

class ImageProcess1 : public QWidget
{
    Q_OBJECT
public:
    explicit ImageProcess1(QWidget *parent = 0);
    
signals:
    
public slots:
    void convertGray();
    // void calcHistogram();
    
public:
    void convertGrayImpl(const TImageRGB& src, TImageRGB& dst);
    // void calcHistogramImpl(const TImageRGB& src, QVector<double>& hist);
    
private:
    TImageView* m_view_left;
    TImageView* m_view_right;
};

#endif // IMAGEPROCESS1_H
