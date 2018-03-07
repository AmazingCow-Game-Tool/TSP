#pragma once

// std
#include <vector>
// TSP
#include "include/Core/Image/Images.h"
#include "include/Core/ImageFinder/ImageFinders.h"

namespace TSP { namespace Core {

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

} // namespace Core
} // namespace TSP
