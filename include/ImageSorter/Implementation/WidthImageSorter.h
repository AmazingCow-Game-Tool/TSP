#pragma once

// TSP
#include "include/ImageSorter/Interface/IImageSorter.h"


class WidthImageSorter :
    public IImageSorter
{
    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    virtual ~WidthImageSorter() = default;


    //------------------------------------------------------------------------//
    // Interface Methods                                                      //
    //------------------------------------------------------------------------//
public:
    int Sort(const Image &img1, const Image &img2) const noexcept override
    {
        return img1.GetSize().width - img2.GetSize().width;
    }

}; // class WidthImageSorter
