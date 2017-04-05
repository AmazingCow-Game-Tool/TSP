#pragma once

//std
#include <algorithm>
//TSP
#include "include/ImageSorter/IImageSorter.h"

class MaxSideImageSorter :
    public IImageSorter
{
    // Interface Methods //
public:
    virtual int sort(const Image &img1, const Image &img2) const override
    {
        auto &s1 = img1.getSize();
        auto &s2 = img2.getSize();

        return std::max(s1.width(), s1.height()) -
               std::max(s2.width(), s2.height());
    }
};

