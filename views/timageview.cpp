#include "timageview.h"
#include <QDebug>

TImageView::TImageView(int winWidth, int winHeight, QWidget *parent)
    :QWidget(parent)
{
    // int winWidth = width();
    // int winHeight = height();
    createDummyImage(winWidth, winHeight);
    QImage temp = m_image.saveToImage();
    m_pixmap = QPixmap::fromImage(temp);
    
    m_validImage = false;
    m_mode = MODE_FIXED;
    
    m_scale = 1.0;
    m_scale_max = 3.0;
    m_scale_min = 1.0 / 3;
    
    m_curPoint = QPoint(0, 0);
    m_downPoint = QPoint(0, 0);
    m_movePoint = QPoint(0, 0);
    m_lButtonDown = false;
    
    m_bkBrush = QBrush(Qt::gray);
}

void TImageView::createDummyImage(int width, int height)
{
    m_image.create(width, height);
    for (int y = 0; y < height; ++y)
    {
        PixelRGB* row_ptr = m_image.rowPtr(y);
        for (int x = 0; x < width; ++x)
        {
            unsigned char v = (x + y) % 255;
            row_ptr[x].red = v;
            row_ptr[x].green = v;
            row_ptr[x].blue = v;
        }
    }
}

void TImageView::setImageFromFile(const QString &fname)
{
    m_image.loadFromFile(fname);
    
    QImage temp = m_image.saveToImage();
    m_pixmap = QPixmap::fromImage(temp);
    m_validImage = true;
    m_scale = 1.0;
    m_curPoint = QPoint(0, 0);
    m_downPoint = QPoint(0, 0);
    m_movePoint = QPoint(0, 0);
    m_lButtonDown = false;
    checkGeometry();
    update();
}

void TImageView::setImage(const QImage &image)
{
    m_image.loadFromImage(image);
    
    QImage temp = m_image.saveToImage();
    m_pixmap = QPixmap::fromImage(temp);
    m_validImage = true;
    m_scale = 1.0;
    m_curPoint = QPoint(0, 0);
    m_downPoint = QPoint(0, 0);
    m_movePoint = QPoint(0, 0);
    m_lButtonDown = false;
    checkGeometry();
    update();
}

void TImageView::checkScale()
{
    m_scale = qBound(m_scale_min, m_scale, m_scale_max);
}

void TImageView::checkGeometry()
{
    if (m_mode == MODE_FIXED)
    {
        int image_width = m_image.width();
        int image_height = m_image.height();
        int win_width = width();
        int win_height = height();
        
        int dx = 0;
        int dy = 0;
        if (image_width < win_width && image_height < win_height)
        {
            // show original resolution
            dx = (win_width - image_width) / 2;
            dy = (win_height - image_height) / 2;
            m_movePoint = QPoint(dx, dy);
            m_scale = 1.0;
        }
        else
        {
            double rx = win_width * 1.0 / image_width;
            double ry = win_height * 1.0 / image_height;
            if (rx > ry)
            {
                m_scale = ry;
                dy = 0;
                dx = (win_width - image_width * m_scale) / 2;
            }
            else
            {
                m_scale = rx;
                dx = 0;
                dy = (win_height - image_height * m_scale) / 2;
            }
            m_movePoint = QPoint(dx, dy);
        }
    }
    else // mode == MODE_ZOOM
    {
        checkScale();
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
}

void TImageView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setBackground(m_bkBrush);
    painter.eraseRect(rect());
    
    // qDebug() << m_pixmap.width() << ", " << m_pixmap.height();
    checkGeometry();
    painter.translate(m_movePoint.x(), m_movePoint.y());
    painter.scale(m_scale, m_scale);
    
    painter.drawPixmap(0, 0, m_pixmap);
}

void TImageView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_lButtonDown = true;
        m_downPoint = event->pos();
        m_curPoint = m_downPoint;
    }
}

void TImageView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_lButtonDown = false;
    }
}

void TImageView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_lButtonDown && m_validImage)
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

void TImageView::wheelEvent(QWheelEvent *event)
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
