#include "imageview.h"
#include <QPainter>
#include <QDebug>
#include <QBrush>

ImageView::ImageView(int win_width, int win_height, QWidget *parent) : QWidget(parent)
{
    if (parent == 0)
    {
        // top level widget
        QSize screenSize = getScreenSize();
        int px = (screenSize.width() - win_width) / 2;
        int py = (screenSize.height() - win_height) / 2;
        setGeometry(px, py, win_width, win_height);
    }
    
    // m_pixmap = QPixmap(QSize(win_width, win_height));
    createDummyImage(m_pixmap, win_width, win_height);
    m_validImage = false;
    // m_pixmap.fill();
    m_movePoint = QPoint(0, 0);
    m_scale = 1.0;
    m_bkBrush = QBrush(Qt::gray);
    
    m_bMouseDown = false;
    m_downPoint = QPoint(0, 0);
    
    m_scale_max = 3.0;
    m_scale_min = 1.0 / 3;
}

bool ImageView::setImage(const QImage &image)
{
    if (image.isNull())
        return false;
    m_pixmap = QPixmap::fromImage(image);
    m_scale = 1.0;
    m_validImage = true;
    checkGeometry();
    update();
    return true;
}

void ImageView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setBackground(m_bkBrush);
    painter.eraseRect(rect());
    
    painter.translate(m_movePoint.x(), m_movePoint.y());
    painter.scale(m_scale, m_scale);
    painter.drawPixmap(0, 0, m_pixmap);
}

void ImageView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bMouseDown = true;
        m_downPoint = QPoint(event->x(), event->y());
        m_curPoint = m_downPoint;
    }
}

void ImageView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) 
    {
        m_bMouseDown = false;
    }
}

void ImageView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bMouseDown && m_validImage)
    {
        int px = event->x();
        int py = event->y();
        int dx = px - m_curPoint.x();
        int dy = py - m_curPoint.y();
        m_curPoint = QPoint(px, py);
        m_movePoint = m_movePoint + QPoint(dx, dy);
        checkGeometry();
        update();
    }
}

void ImageView::wheelEvent(QWheelEvent *event)
{
    if (!m_validImage)
        return;
    double z1 = m_scale;
    if (event->delta() > 0)
        m_scale *= 1.2;
    else
        m_scale /= 1.2;
    
    checkScale();
    double z2 = m_scale;
    
    int px = event->x();
    int py = event->y();
    int dx = px - m_movePoint.x();
    int dy = py - m_movePoint.y();
    dx = int(dx * z2 / z1);
    dy = int(dy * z2 / z1);
    m_movePoint = QPoint(px - dx, py - dy);
    checkGeometry();
    update();
}

void ImageView::zoomIn()
{
    m_scale = m_scale * 1.2;
}

void ImageView::zoomOut()
{
    m_scale = m_scale / 1.2;
}

QSize ImageView::getScreenSize()
{
    return QSize(1440, 900);
}

void ImageView::checkScale()
{
    m_scale = qBound(m_scale_min, m_scale, m_scale_max);
}

void ImageView::checkGeometry()
{
    int winWidth = width();
    int winHeight = height();
    int imageWidth = int(m_pixmap.width() * m_scale);
    int imageHeight = int(m_pixmap.height() * m_scale);
    
    int move_x = 0;
    int move_y = 0;
    
    if (imageWidth < winWidth)
        move_x = (winWidth - imageWidth) / 2;
    else
    {
        if (m_movePoint.x() > 0)
            move_x = 0;
        else if (m_movePoint.x() < -(imageWidth - winWidth))
            move_x = -(imageWidth - winWidth);
        else
            move_x = m_movePoint.x();
    }
    
    if (imageHeight < winHeight)
        move_y = (winHeight - imageHeight) / 2;
    else
    {
        if (m_movePoint.y() > 0)
            move_y = 0;
        else if (m_movePoint.y() < -(imageHeight - winHeight))
            move_y = -(imageHeight - winHeight);
        else
            move_y = m_movePoint.y();
    }
    m_movePoint = QPoint(move_x, move_y);
}

void ImageView::createDummyImage(QPixmap &pixmap, int width, int height)
{
    QImage image = QImage(width, height, QImage::Format_RGB888);
    unsigned char* image_data = image.bits();
    int bytesPerLine = image.bytesPerLine();
    for (int j = 0; j < image.height(); ++j)
    {
        unsigned char* row_ptr = image_data + j * bytesPerLine;
        for (int i = 0; i < image.width(); ++i)
        {
            unsigned char v = (i + j) % 255;
            row_ptr[i * 3 + 0] = v;
            row_ptr[i * 3 + 1] = v;
            row_ptr[i * 3 + 2] = v;
        }
    }
    pixmap = QPixmap::fromImage(image);
}

void ImageView::adjustImageFitWindow()
{
    int winWidth = width();
    int winHeight = height();
    int imageWidth = m_pixmap.width();
    int imageHeight = m_pixmap.height();
    double rx = winWidth * 1.0 / imageWidth;
    double ry = winHeight * 1.0 / imageHeight;
    if (rx > ry)
        m_scale = rx;
    else
        m_scale = ry;
    checkGeometry();
    update();
}

void ImageView::adjustImageFullWindow()
{
    int winWidth = width();
    int winHeight = height();
    int imageWidth = m_pixmap.width();
    int imageHeight = m_pixmap.height();
    double rx = winWidth * 1.0 / imageWidth;
    double ry = winHeight * 1.0 / imageHeight;
    if (rx > ry)
        m_scale = ry;
    else
        m_scale = rx;
    checkGeometry();
    update();
}
