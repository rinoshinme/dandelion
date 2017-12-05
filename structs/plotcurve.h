#ifndef PLOTCURVE_H
#define PLOTCURVE_H

#include <QVector>
#include <QPointF>
#include <QRgb>

class PlotCurve
{
public:
    enum LINE_STYLE
    {
        STYLE_NONE,
        STYLE_SOLID,
        STYLE_DASH,
        STYLE_DOTTED,
    };
    
public:
    PlotCurve() {}
    ~PlotCurve() {}
    
public:
    void setPoints(const QVector<QPointF>& points);
    void setPoints(qreal* xs, qreal* ys, int n);
    void setPoints(QPointF* points, int n);
    
    void addPoint(qreal x, qreal y);
    // void addPoint(QPointF& pt);
    // void addPoints(QVector<QPointF>& pts);
    
    void setLineStyle(int style);
    void setLineColor(QRgb color);
    // void setLineWidth();
    
    bool isEmpty() const;
    int size() const { return m_points.size(); }
    
    qreal xMax() const;
    qreal xMin() const;
    qreal yMax() const;
    qreal yMin() const;
    
    QVector<QPointF> getPoints() { return m_points; }
    QPointF operator[](int index) const { return m_points[index]; }
    
private:
    QVector<QPointF> m_points; // double value coordinates
    int m_lineStyle; // None, Solid, ...
    QRgb m_lineColor;
};

#endif // PLOTCURVE_H
