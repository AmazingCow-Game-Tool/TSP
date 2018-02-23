#pragma once

// std
#include <vector>
// TSP
#include "include/Image/Images.h"
#include "include/ImageFinder/ImageFinders.h"


class IImageLoader
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedef                                            //
    //------------------------------------------------------------------------//
public:
    ACOW_SMART_PTRS_OF(IImageLoader);

    //------------------------------------------------------------------------//
    // Interface Methods                                                      //
    //------------------------------------------------------------------------//
public:
    virtual std::vector<Image::SPtr> LoadImages(IImageFinder::SPtr pImageFinder) = 0;

}; // class IImageLoader
