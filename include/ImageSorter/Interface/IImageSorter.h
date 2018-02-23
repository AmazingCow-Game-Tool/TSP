#pragma once

// TSP
#include "include/Image.h"

class IImageSorter
{
    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    virtual ~IImageSorter() = default;

    //------------------------------------------------------------------------//
    // Interface Methods                                                      //
    //------------------------------------------------------------------------//
public:
    virtual int Sort(const Image &img1, const Image &img2) const noexcept = 0;

}; // class IImageSorter
