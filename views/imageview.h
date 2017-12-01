#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QtGui>
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QWheelEvent>
#include <QMouseEvent>

#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 720

class ImageView : public QWidget
{
    Q_OBJECT
public:
    explicit ImageView(int win_width = DEFAULT_WIDTH, 
                       int win_height = DEFAULT_HEIGHT, 
                       QWidget *parent = 0);
    ~ImageView() {
        qDebug() << "destructor!\n";
    }
signals:
    
public slots:
    bool setImage(const QImage& image);
    // void setImage(const QString& filename);
    void seBkBrush(const QBrush& brush) { m_bkBrush = brush; }
    void adjustImageFitWindow();
    void adjustImageFullWindow();
    void zoomIn();
    void zoomOut();
    
public:
    // events
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    
public:
    // create initial image to represent nothing
    void createDummyImage(QPixmap& pixmap, int width, int height);
    void checkGeometry();
    void checkScale();
    QSize getScreenSize();
    
private:
    QPixmap m_pixmap;
    bool m_validImage;
    QPoint m_curPoint; // temp variable
    bool m_bMouseDown;
    QPoint m_downPoint;
    
    QPoint m_movePoint; // position of up-left corner in widget
    double m_scale;
    double m_scale_max;
    double m_scale_min;
    QBrush m_bkBrush;
};

#endif // IMAGEVIEW_H
