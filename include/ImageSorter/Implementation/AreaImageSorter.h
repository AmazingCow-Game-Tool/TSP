#pragma once

// TSP
#include "include/ImageSorter/Interface/IImageSorter.h"

class AreaImageSorter :
    public IImageSorter
{
    //------------------------------------------------------------------------//
    // Interface Methods                                                      //
    //------------------------------------------------------------------------//
public:
    int Sort(const Image &img1, const Image &img2) const noexcept override
    {
        auto &s1 = img1.GetSize();
        auto &s2 = img2.GetSize();

        return (s1.width * s1.height) - (s2.width * s2.height);
    }

}; // class AreaImageSorter
