#pragma once

// std
#include <vector>
#include <string>
// TSP
#include "include/Core/ImageLoader/Interface/IImageLoader.h"

namespace TSP { namespace Core {

class ImageLoader
    : public IImageLoader
{
    //------------------------------------------------------------------------//
    // Public Methods                                                         //
    //------------------------------------------------------------------------//
public:
    std::vector<Image::SPtr> LoadImages(IImageFinder::SPtr pImageFinder) override;

}; // class ImageLoader

} // namespace Core
} // namespace TSP