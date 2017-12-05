#include "histview.h"

#include <QPainter>
#include <QDebug>

HistView::HistView(QWidget *parent) : QWidget(parent)
{
    m_bkBrush = QBrush(Qt::gray);
    m_fgBrush = QBrush(Qt::blue);
    // m_lineBrush = QBrush(Qt::black);
    
    m_values.resize(10);
    for (int i = 0; i < m_values.size(); ++i)
        m_values[i] = i * i;
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
    painter.eraseRect(rect());
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
        int x = i * binWidth;
        int w = binWidth;
        int y = (1.0 - (m_values[i] - min_value) / (max_value - min_value)) * winHeight;
        int h = winHeight - y;
        QRect rect(x, y, w, h);
        painter.drawRect(rect);
    }
    // update();
}
