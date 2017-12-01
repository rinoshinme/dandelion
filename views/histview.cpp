#include "histview.h"

#include <QPainter>

HistView::HistView(QWidget *parent) : QWidget(parent)
{
    m_bkBrush = QBrush(Qt::white);
    m_fgBrush = QBrush(Qt::blue);
    m_lineBrush = QBrush(Qt::black);
}

void HistView::setValues(const QVector<double> vs)
{
    int n = vs.size();
    m_values.resize(n);
    for (int i = 0; i < n; ++i)
        m_values[i] = vs[i];
}

void HistView::setValues(double *arr, int n)
{
    m_values.resize(n);
    for (int i = 0; i < n; ++i)
        m_values[i] = arr[i];
}

void HistView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    if (m_values.size() == 0)
        return;
    
    QPainter painter(this);
    painter.setBackground(m_bkBrush);
    painter.setBrush(m_fgBrush);
    double min_value = 1.0e10;
    double max_value = -1.0e10;
    for (int i = 0; i < m_values.size(); ++i)
    {
        if (m_values[i] > max_value)
            max_value = m_values[i];
        if (m_values[i] < min_value)
            min_value = m_values[i];
    }
    min_value = (min_value < 0) ? min_value : 0;
    
    int winWidth = width();
    int winHeight = height();
    int binWidth = winWidth / m_values.size();
    
    for (int i = 0; i < m_values.size(); ++i)
    {
        int x1 = i * binWidth;
        int x2 = (i + 1) * binWidth;
        int y1 = (1.0 - (m_values[i] - min_value) / (max_value - min_value)) * winHeight;
        int y2 = winHeight;
        QRect rect(x1, y1, x2, y2);
        painter.drawRect(rect);
    }
    update();
}
