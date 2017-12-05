#include "plotview.h"
#include <QPainter>
#include <cmath>
#include <QDebug>

#define PI 3.14

PlotView::PlotView(QWidget *parent) : QWidget(parent)
{
    PlotCurve curve;
    for (int i = 0; i < 100; ++i)
        curve.addPoint(i * 1.0, std::sin(i * PI / 30) * 50);
    m_curves.push_back(curve);
    
    m_boxLeft = width() / 8;
    m_boxWidth = width() * 3 / 4;
    m_boxTop = height() / 8;
    m_boxHeight = height() * 3 / 4;
    
    m_xmin = 0;
    m_xmax = 0;
    m_ymin = 0;
    m_ymax = 0;
    
    m_scaleX = 1.0;
    m_scaleY = 1.0;
    m_Origin = QPointF(0, 0);
}

void PlotView::getCurveMaxMins()
{
    if (m_curves.size() == 0)
        return;
    
    m_xmin = m_curves[0].xMin();
    m_xmax = m_curves[0].xMax();
    m_ymin = m_curves[0].yMin();
    m_ymax = m_curves[0].yMax();
    
    for (int i = 1; i < m_curves.size(); ++i)
    {
        qreal v1 = m_curves[i].xMin();
        if (v1 < m_xmin)
            m_xmin = v1;
        qreal v2 = m_curves[i].xMax();
        if (v2 > m_xmax)
            m_xmax = v2;
        qreal v3 = m_curves[i].yMin();
        if (v3 < m_ymin)
            m_ymin = v3;
        qreal v4 = m_curves[i].yMax();
        if (v4 > m_ymax)
            m_ymax = v4;
    }
}

void PlotView::checkGeometry()
{
    m_Origin.setX(m_xmin);
    m_Origin.setY(m_ymin);
    m_scaleX = m_boxWidth * 1.0 / (m_xmax - m_xmin);
    m_scaleY = -m_boxHeight * 1.0 / (m_ymax - m_ymin);
}

void PlotView::drawCurve(QPainter &painter, const PlotCurve &curve)
{
    QVector<QPoint> points;
    for (int i = 0; i < curve.size(); ++i)
    {
        QPointF pt = curve[i];
        double fx = (pt.x() - m_Origin.x()) * m_scaleX + m_boxLeft;
        double fy = (pt.y() - m_Origin.y()) * m_scaleY + m_boxTop + m_boxHeight;
        QPoint pt2 = QPoint(int(fx), int(fy));
        points.push_back(pt2);
    }
    for (int i = 1; i < points.size(); ++i)
        painter.drawLine(points[i - 1], points[i]);
}

void PlotView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    m_boxLeft = width() / 8;
    m_boxWidth = width() * 3 / 4;
    m_boxTop = height() / 8;
    m_boxHeight = height() * 3 / 4;
    update();
}

void PlotView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setBackground(Qt::white);
    painter.eraseRect(rect());
    
    // draw bounding box
    QRect bbox(m_boxLeft, m_boxTop, m_boxWidth, m_boxHeight);
    painter.drawRect(bbox);
    
    // draw curve
    if (m_curves.size() > 0)
    {
        getCurveMaxMins();
        checkGeometry();
        for (int k = 0; k < m_curves.size(); ++k)
            drawCurve(painter, m_curves[k]);
    }
}
