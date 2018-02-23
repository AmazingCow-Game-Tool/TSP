#pragma once

// TSP
#include "include/ImageSorter/Interface/IImageSorter.h"

class HeightImageSorter :
    public IImageSorter
{
    //------------------------------------------------------------------------//
    // Interface Methods                                                      //
    //------------------------------------------------------------------------//
public:
    int Sort(const Image &img1, const Image &img2) const noexcept override
    {
        return img1.GetSize().height - img2.GetSize().height;
    }

}; // class HeightImageSorter
