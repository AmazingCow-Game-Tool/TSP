#pragma once

// std
#include <vector>
#include <string>
// TSP
#include "include/ImageLoader/Interface/IImageLoader.h"


class ImageLoader
    : public IImageLoader
{
    //------------------------------------------------------------------------//
    // Public Methods                                                         //
    //------------------------------------------------------------------------//
public:
    std::vector<Image::SPtr> LoadImages(IImageFinder::SPtr pImageFinder) override;


}; // class ImageLoader
