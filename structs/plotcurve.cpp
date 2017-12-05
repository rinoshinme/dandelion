#include "plotcurve.h"



void PlotCurve::setPoints(const QVector<QPointF> &points)
{
    // explicit copy
    m_points.resize(points.size());
    for (int i = 0; i < points.size(); ++i)
        m_points[i] = points[i];
}

void PlotCurve::setPoints(QPointF *points, int n)
{
    m_points.resize(n);
    for (int i = 0; i < n; ++i)
        m_points[i] = points[i];
}

void PlotCurve::setPoints(qreal *xs, qreal *ys, int n)
{
    m_points.resize(n);
    for (int i = 0; i < n; ++i)
    {
        m_points[i].setX(xs[i]);
        m_points[i].setY(ys[i]);
    }
}

void PlotCurve::addPoint(qreal x, qreal y)
{
    m_points.push_back(QPointF(x, y));
}

void PlotCurve::setLineStyle(int style)
{
    m_lineStyle = style;
}

void PlotCurve::setLineColor(QRgb color)
{
    m_lineColor = color;
}

bool PlotCurve::isEmpty() const
{
    return (m_points.size() == 0);
}

qreal PlotCurve::xMax() const
{
    if (m_points.size() == 0)
        return 0.0;
    qreal max_value = m_points[0].x();
    for (int i = 1; i < m_points.size(); ++i)
    {
        if (m_points[i].x() > max_value)
            max_value = m_points[i].x();
    }
    return max_value;
}

qreal PlotCurve::xMin() const
{
    if (m_points.size() == 0)
        return 0.0;
    qreal min_value = m_points[0].x();
    for (int i = 1; i < m_points.size(); ++i)
    {
        if (m_points[i].x() < min_value)
            min_value = m_points[i].x();
    }
    return min_value;
}

qreal PlotCurve::yMax() const
{
    if (m_points.size() == 0)
        return 0.0;
    qreal max_value = m_points[0].y();
    for (int i = 1; i < m_points.size(); ++i)
    {
        if (m_points[i].y() > max_value)
            max_value = m_points[i].y();
    }
    return max_value;
}

qreal PlotCurve::yMin() const
{
    if (m_points.size() == 0)
        return 0.0;
    qreal min_value = m_points[0].y();
    for (int i = 1; i < m_points.size(); ++i)
    {
        if (m_points[i].y() < min_value)
            min_value = m_points[i].y();
    }
    return min_value;
}





















