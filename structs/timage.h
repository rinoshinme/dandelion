#ifndef TIMAGE_H
#define TIMAGE_H

#include <QImage>
#include "pixel.h"

/*
 * T: unsigned char
 * T: PixelBGR
 * support image format: 8, 24, 32
 */
template<typename T>
class TImage
{
protected:
    T* m_data;
    int m_width;
    int m_height;
    
public:
    TImage()
    {
        m_data = 0;
        m_width = 0;
        m_height = 0;
    }
    
    TImage(const QString& fname) {}
    
public:
    int width() const { return m_width; }
    int height() const { return m_height; }
    T* dataPtr() const { return m_data; }
    T* rowPtr(int r) const { return m_data + r * m_width; }
    
    void create(int width, int height)
    {
        if (m_data != 0)
            delete[] m_data;
        m_width = width;
        m_height = height;
        m_data = new T[m_width * m_height];
        memset(m_data, 0, m_width * m_height * sizeof(T));
    }
};

class TImage8U : public TImage<Pixel8U>
{
public:
    TImage8U()
    {
        m_data = 0;
        m_width = 0;
        m_height = 0;
    }

    TImage8U(const QString& fname)
    {
        QImage image;
        image.load(fname);
        loadFromImage(image);
    }
    
public:
    inline void loadFromImage(const QImage &image)
    {
        if (m_data != 0)
            delete[] m_data;
        m_width = image.width();
        m_height = image.height();
        m_data = new Pixel8U[m_width * m_height];
        
        const unsigned char* src_data = image.bits();
        int lineByte = image.bytesPerLine();
        int depth = image.depth();
        for (int y = 0; y < m_height; ++y)
        {
            const unsigned char* src_row_ptr = src_data + y * lineByte;
            unsigned char* dst_row_ptr = m_data + y * m_width;
            if (depth == 8)
            {
                for (int x = 0; x < m_width; ++x)
                    dst_row_ptr[x] = src_row_ptr[x];
            }
            else
            {
                int d = depth / 8;
                for (int x = 0; x < m_width; ++x)
                {
                    unsigned char red = src_row_ptr[d * x + 2];
                    unsigned char green = src_row_ptr[d * x + 1];
                    unsigned char blue = src_row_ptr[d * x + 0];
                    dst_row_ptr[x] = PixelRGB(red, green, blue).toGray();
                }
            }
        }
    }
    
    inline void loadFromFile(const QString& fname)
    {
        QImage image;
        image.load(fname);
        loadFromImage(image);
    }
    
    inline QImage saveToImage()
    {
        int lineByte = (m_width + 3) / 4 * 4;
        return QImage(m_data, m_width, m_height, lineByte, QImage::Format_Grayscale8);
    }
    
    inline void saveToFile(const QString& fname)
    {
        QImage image = saveToImage();
        image.save(fname);
    }
};

class TImageRGB : public TImage<PixelRGB>
{
public:
    TImageRGB()
    {
        m_data = 0;
        m_width = 0;
        m_height = 0;
    }

    TImageRGB(const QString& fname)
    {
        QImage image;
        image.load(fname);
        loadFromImage(image);
    }
    
public:
    inline void loadFromImage(const QImage &image)
    {
        if (m_data != 0)
            delete[] m_data;
        m_width = image.width();
        m_height = image.height();
        m_data = new PixelRGB[m_width * m_height];
        
        const unsigned char* src_data = image.bits();
        int lineByte = image.bytesPerLine();
        int depth = image.depth();
        for (int y = 0; y < m_height; ++y)
        {
            const unsigned char* src_row_ptr = src_data + y * lineByte;
            PixelRGB* dst_row_ptr = m_data + y * m_width;
            if (depth == 8)
            {
                for (int x = 0; x < m_width; ++x)
                {
                    dst_row_ptr[x].red = src_row_ptr[x];
                    dst_row_ptr[x].green = src_row_ptr[x];
                    dst_row_ptr[x].blue = src_row_ptr[x];
                }
            }
            else
            {
                int d = depth / 8;
                for (int x = 0; x < m_width; ++x)
                {
                    dst_row_ptr[x].red = src_row_ptr[x * d + 2];
                    dst_row_ptr[x].green = src_row_ptr[x * d + 1];
                    dst_row_ptr[x].blue = src_row_ptr[x  * d + 0];
                }
            }
        }
    }
    
    inline void loadFromFile(const QString& fname)
    {
        QImage image;
        image.load(fname);
        loadFromImage(image);
    }
    
    inline QImage saveToImage()
    {
        // int lineByte = (m_width * 3 + 3) / 4 * 4;
        return QImage((reinterpret_cast<unsigned char*>(m_data)), m_width, m_height, QImage::Format_RGB888);
    }
    
    inline void saveToFile(const QString& fname)
    {
        QImage image = saveToImage();
        image.save(fname);
    }
};

#endif // TIMAGE_H
