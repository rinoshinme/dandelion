#ifndef TIMAGE_H
#define TIMAGE_H

#include <QImage>

template<typename T>
class TImage
{
private:
    T* m_data;
    int m_width;
    int m_height;
    
public:
    TImage();
    TImage(const QString& fname);
private:
    TImage(const TImage<T>& copy);
    TImage<T> operator=(const TImage<T>& copy);
    
public:
    int width() const { return m_width; }
    int height() const { return m_height; }
    T* dataPtr() const { return m_data; }
    T* rowPtr(int r) const { return m_data + r * m_width; }

    void FromImage(const QImage& img);
    void ToImage(QImage& img);
    
};

#endif // TIMAGE_H
