#include "imageprocess1.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

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
    
    QImage image;
    image.load("F:\\data\\test\\timg.jpg");
    m_view_left->setImage(image);
}

ImageProcess1::~ImageProcess1()
{
    
}

void ImageProcess1::convertGray()
{
    convertGrayImpl(m_view_left->image(), m_view_right->image());
    update();
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
