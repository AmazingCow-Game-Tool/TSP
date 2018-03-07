#pragma once

// TSP
#include "include/Core/Image/Images.h"

namespace TSP { namespace Core {

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
    virtual int Sort(const Image::SPtr &img1, const Image::SPtr &img2) const noexcept = 0;

}; // class IImageSorter

} // namespace Core
} // namespace TSP
