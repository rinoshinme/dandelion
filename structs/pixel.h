#ifndef PIXEL_H
#define PIXEL_H

typedef unsigned char Pixel8U;

struct PixelRGB
{
    Pixel8U red;
    Pixel8U green;
    Pixel8U blue;
    
    PixelRGB(Pixel8U r = 0, Pixel8U g = 0, Pixel8U b = 0)
        :red(r), green(g), blue(b) {}
    
    Pixel8U toGray() const
    {
        return static_cast<Pixel8U>(0.299 * red + 0.587 * green + 0.114 * blue);
    }
};

#endif // PIXEL_H
