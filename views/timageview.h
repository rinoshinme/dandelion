#ifndef TIMAGEVIEW_H
#define TIMAGEVIEW_H

#include "imageview.h"
#include "../structs/timage.h"

class TImageView : public QWidget
{
    Q_OBJECT
public:
    enum VIEW_MODE { MODE_FIXED, MODE_ZOOM, };
public:
    explicit TImageView(int winWidth = DEFAULT_IMAGE_WIDTH,
                        int winHeight = DEFAULT_IMAGE_HEIGHT,
                        QWidget *parent = 0);
    
public:
    TImageRGB& image() { return m_image; }
    
signals:
    
public slots:
    void setImage(const QImage& image);
    void setImageFromFile(const QString& fname);
    void setMode(VIEW_MODE mode) { m_mode = mode; }
    
public:
    // events
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    
public:
    void createDummyImage(int width, int height);
    void checkGeometry();
    void checkScale();
    
private:
    TImageRGB m_image;
    QPixmap m_pixmap;
    bool m_validImage;
    VIEW_MODE m_mode;
    
    double m_scale;
    double m_scale_max;
    double m_scale_min;
    
    QPoint m_curPoint;
    QPoint m_downPoint;
    QPoint m_movePoint;
    bool m_lButtonDown;
    
    QBrush m_bkBrush;
};

#endif // TIMAGEVIEW_H
