#pragma once

// std
#include <string>
#include <vector>
// TSP
#include "include/Core/Image/Images.h"

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
    virtual std::vector<Image::SPtr> LoadImages(
        const std::vector<std::string> &paths) = 0;

}; // class IImageLoader

} // namespace Core
} // namespace TSP
