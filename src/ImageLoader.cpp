// Header
#include "include/ImageLoader.h"


//----------------------------------------------------------------------------//
// CTOR                                                                       //
//----------------------------------------------------------------------------//
ImageLoader::ImageLoader(const std::vector<std::string> &imagePaths) :
    m_imagePaths(imagePaths)
{
    // Empty...
}


//----------------------------------------------------------------------------//
// Public Methods                                                             //
//----------------------------------------------------------------------------//
std::vector<Image> ImageLoader::loadImages()
{
    std::vector<Image> images;
    for(const auto &path : m_imagePaths)
    {
        auto image = Image::LoadFromFile(path);
        images.push_back(image);
    }

    return images;
}
