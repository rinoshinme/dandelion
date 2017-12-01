#ifndef WAVEVIEW_H
#define WAVEVIEW_H

#include <QWidget>
#include <QBrush>
#include <QPen>

// class for showing sound waveforms
class WaveView : public QWidget
{
    Q_OBJECT
public:
    explicit WaveView(QWidget *parent = 0);
    ~WaveView();
    
signals:
    
public slots:
    // void setWave();
    
public:
    // QVector<double> getNormalizeData();
    // events
    void paintEvent(QPaintEvent* event);
    
private:
    double* m_data;
    int m_len;
    int m_start;
    int m_end;
    
    double m_max_value;
    double m_min_value;
    
    QBrush m_bkBrush;
    QPen m_linePen;
};

#endif // WAVEVIEW_H
