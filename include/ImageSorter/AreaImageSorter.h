#pragma once

//TSP
#include "include/ImageSorter/IImageSorter.h"

class AreaImageSorter :
    public IImageSorter
{
    // Interface Methods //
public:
    virtual int sort(const Image &img1, const Image &img2) const override
    {
        auto &s1 = img1.getSize();
        auto &s2 = img2.getSize();

        return (s1.width() * s1.height())  - (s2.width() * s2.height());
    }
};

