#include "imageprocess1.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "../structs/timage.h"
#include "../views/histview.h"

ImageProcess1::ImageProcess1(QWidget *parent) : QWidget(parent)
{
    m_view_left = new TImageView(640, 480, this);
    m_view_right = new TImageView(640, 480, this);
    
    QPushButton* btnGray = new QPushButton(tr("convert"), this);
    QPushButton* btnHist = new QPushButton(tr("hist"), this);
    QVBoxLayout* btnLayout = new QVBoxLayout;
    btnLayout->addWidget(btnGray);
    btnLayout->addWidget(btnHist);
    btnLayout->addStretch();
    QHBoxLayout* gLayout = new QHBoxLayout;
    gLayout->addWidget(m_view_left);
    gLayout->addWidget(m_view_right);
    gLayout->addLayout(btnLayout);
    
    setLayout(gLayout);
    
    setWindowTitle("ImageProcess1");
    connect(btnGray, SIGNAL(clicked()), this, SLOT(convertGray()));
    connect(btnHist, SIGNAL(clicked()), this, SLOT(calcHistogram()));
    
    m_view_left->setSize(640, 480);
    m_view_right->setSize(640, 480);
    m_view_left->setMode(TImageView::MODE_ZOOM);
    m_view_right->setMode(TImageView::MODE_FIXED);
    
    QImage image;
    image.load("F:\\data\\test\\timg.jpg");
    m_view_left->setImage(image);
}

void ImageProcess1::convertGray()
{
    TImageRGB result;
    convertGrayImpl(m_view_left->image(), result);
    // QImage imgDisplay = result.saveToImage();
    // m_view_right->setImage(imgDisplay);
    m_view_right->setImage(result);
}

void ImageProcess1::convertGrayImpl(const TImageRGB &src, TImageRGB &dst)
{
    int width = src.width();
    int height = src.height();
    dst.create(width, height);
    for (int y = 0; y < height; ++y)
    {
        PixelRGB* row_src = src.rowPtr(y);
        PixelRGB* row_dst = dst.rowPtr(y);
        for (int x = 0; x < width; ++x)
        {
            Pixel8U v = row_src[x].toGray();
            row_dst[x].red = v;
            row_dst[x].green = v;
            row_dst[x].blue = v;
        }
    }
}

void ImageProcess1::calcHistogram()
{
    QVector<int> hist;
    calcHistogramImpl(m_view_left->image(), hist);
    QVector<double> histd;
    histd.resize(hist.size());
    for (int i = 0; i < hist.size(); ++i)
        histd[i] = hist[i] * 1.0;
    
    HistView* view = new HistView;
    view->setValues(histd);
    view->show();
}

void ImageProcess1::calcHistogramImpl(const TImageRGB &src, QVector<int> &hist)
{
    hist.resize(256);
    for (int i = 0; i < 256; ++i)
        hist[i] = 0;
    
    for (int j = 0; j < src.height(); ++j)
    {
        PixelRGB* row_src = src.rowPtr(j);
        for (int i = 0; i < src.width(); ++i)
        {
            Pixel8U v = row_src[i].toGray();
            hist[v] += 1;
        }
    }
}
