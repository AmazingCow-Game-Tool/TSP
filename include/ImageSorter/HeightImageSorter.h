#pragma once

//TSP
#include "include/ImageSorter/IImageSorter.h"

class HeightImageSorter :
    public IImageSorter
{
    // CTOR / DTOR //
public:
    virtual ~IImageSorter();

    // Interface Methods //
public:
    virtual int sort(const Image &img1, const Image &img2) const override
    {
        return img1.getSize().height() - img2.getSize().height();
    }
};

