#pragma once

// acow_cpp_goodies
#include "acow/cpp_goodies.h"
// TSP
#include "include/Core/Image/Images.h"

namespace TSP { namespace Core {

class IImageSorter
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    ACOW_UNIQUE_PTR_OF(IImageSorter);


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
