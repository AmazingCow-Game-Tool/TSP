// Header
#include "include/Core/ImageLoader/Implementation/ImageLoader.h"

// Usings
using namespace TSP;
using namespace Core;


//----------------------------------------------------------------------------//
// Interface Methods                                                          //
//----------------------------------------------------------------------------//
std::vector<Image::SPtr>
ImageLoader::LoadImages(IImageFinder::SPtr pImageFinder)
{
    auto image_paths = pImageFinder->FindImagesPaths();
    auto images      = std::vector<Image::SPtr>();

    images.reserve(image_paths.size());

    for(const auto &path : image_paths)
    {
        auto p_image = Image::LoadFromFile(path);
        images.push_back(std::move(p_image));
    }

    return images;
}
