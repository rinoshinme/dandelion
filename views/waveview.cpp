#include "waveview.h"
#include <QPainter>
#include <cmath>
#include <QDebug>

#ifndef M_PI
#define M_PI 3.1415
#endif

WaveView::WaveView(QWidget *parent) : QWidget(parent)
{
    m_data = 0;
    m_len = 0;
    m_start = 0;
    m_end = 0;
    m_max_value = 1.0;
    m_min_value = -1.0;
    
    m_bkBrush = QBrush(Qt::white);
    m_linePen = QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap);
    
    // create a sinesoidal wave
    m_len = 1024 * 100;
    m_start = 0;
    m_end = 256 * 50;
    m_data = new double[m_len];
    for (int i = 0; i < m_len; ++i)
        m_data[i] = std::sin(i * M_PI / 180) * sin(i * 1.0 / 1000);
    
    m_step_size = 10;
    m_time_interval = 1;
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateData()));
    m_timer->setInterval(m_time_interval);
    m_timer->start();
    cnt = 0;
    m_pixmap = 0;
}

WaveView::~WaveView()
{
    if (m_data != 0)
        delete[] m_data;
    if (m_timer != 0)
    {
        m_timer->stop();
        delete m_timer;
    }
}

void WaveView::updateData()
{
    // cnt += 1;
    // qDebug() << "update data, cnt = " << cnt;
    int delta = m_end - m_start;
    m_start += m_step_size;
    m_end += m_step_size;
    
    if (m_end > m_len)
    {
        m_end = m_len;
        m_start = m_end - delta;
    }
    // m_timer->start();
    update();
}

void WaveView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    if (m_pixmap != 0)
        delete m_pixmap;
    m_pixmap = new QPixmap(size());
    QPainter painter(m_pixmap);
    
    painter.eraseRect(rect());
    painter.setBackground(m_bkBrush);
    
    int winWidth = width();
    int winHeight = height();
    
    // draw center line
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
    painter.drawLine(0, winHeight / 2, winWidth, winHeight / 2);
    // draw wave
    painter.setPen(m_linePen);
    int num_points = m_end - m_start;
    double binWidth = winWidth * 1.0 / num_points;
    
    for (int i = 0; i < num_points - 1; ++i)
    {
        int x1 = int(i * binWidth);
        int x2 = int((i + 1) * binWidth);
        int y1 = (m_data[i + m_start] * winHeight + winHeight) / 2;
        int y2 = (m_data[i + m_start + 1] * winHeight + winHeight) / 2;
        painter.drawLine(x1, y1, x2, y2);
    }
    
    QPainter painter2(this);
    painter2.drawPixmap(0, 0, *m_pixmap);
    // double buffering:
    // draw new frame to m_pixmap
    // and load m_pixmap to window
}
