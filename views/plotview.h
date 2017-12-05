#ifndef PLOTVIEW_H
#define PLOTVIEW_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QPainter>

#include "../structs/plotcurve.h"

/*
 * view for ploting arbitrary curves.
 */
class PlotView : public QWidget
{
    Q_OBJECT
public:
    explicit PlotView(QWidget *parent = 0);
    
signals:
    
public slots:
    
public:
    // events
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent *event);
    
private:
    void getCurveMaxMins();
    void checkGeometry(); // get appropriate scale and trans.
    void drawCurve(QPainter& painter, const PlotCurve& curve);
    
private:
    QVector<PlotCurve> m_curves;
    
    int m_boxLeft;
    int m_boxWidth;
    int m_boxTop;
    int m_boxHeight;
    
    qreal m_xmin;
    qreal m_xmax;
    qreal m_ymin;
    qreal m_ymax;
    
    double m_scaleX;
    double m_scaleY;
    QPointF m_Origin;
    
};

#endif // PLOTVIEW_H
