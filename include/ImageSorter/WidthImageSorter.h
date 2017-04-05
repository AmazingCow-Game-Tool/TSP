#pragma once

//TSP
#include "include/ImageSorter/IImageSorter.h"

class WidthImageSorter :
    public IImageSorter
{
    // CTOR / DTOR //
public:
    virtual ~WidthImageSorter() {}

    // Interface Methods //
public:
    virtual int sort(const Image &img1, const Image &img2) const override
    {
        return img1.getSize().width() - img2.getSize().width();
    }
};
