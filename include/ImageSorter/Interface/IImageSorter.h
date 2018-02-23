#pragma once

// AmazingCow Libs
#include "acow/cpp_goodies.h"
// TSP
#include "include/Image/Images.h"

class IImageSorter
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    ACOW_SMART_PTRS_OF(IImageSorter);


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    virtual ~IImageSorter() = default;


    //------------------------------------------------------------------------//
    // Interface Methods                                                      //
    //------------------------------------------------------------------------//
public:
    virtual int Sort(
        const Image::SPtr &pImg1,
        const Image::SPtr &pImg2) const noexcept = 0;

}; // class IImageSorter
