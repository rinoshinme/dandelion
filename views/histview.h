#ifndef HISTVIEW_H
#define HISTVIEW_H

#include <QWidget>
#include <QVector>
#include <QBrush>

class HistView : public QWidget
{
    Q_OBJECT
public:
    explicit HistView(QWidget *parent = 0);
    
signals:
    
public slots:
    void setValues(const QVector<double> vs);
    void setValues(double* arr, int n);
    void setBkBrush(const QBrush& brush) { m_bkBrush = brush; }
    void setFgBrush(const QBrush& brush) { m_fgBrush = brush; }
    
public:
    // events
    void paintEvent(QPaintEvent* event);
    
private:
    QVector<double> m_values;
    QBrush m_bkBrush;
    QBrush m_fgBrush;
    QBrush m_lineBrush;
    
};

#endif // HISTVIEW_H
