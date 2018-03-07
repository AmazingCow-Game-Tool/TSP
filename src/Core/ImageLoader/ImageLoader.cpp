// Header
#include "include/Core/ImageLoader/Implementation/ImageLoader.h"
// TSP
#include "include/Core/private/Logger.h"

// Usings
using namespace TSP;
using namespace Core;


//----------------------------------------------------------------------------//
// Interface Methods                                                          //
//----------------------------------------------------------------------------//
std::vector<Image::SPtr>
ImageLoader::LoadImages(const std::vector<std::string> &paths)
{
    auto images = std::vector<Image::SPtr>();
    images.reserve(paths.size());

    Core::Logger()->Debug("Starting loading (%d) images.", paths.size());
    for(const auto &path : paths)
    {
        Core::Logger()->Debug(
            "Loading Image (%d/%d) - Path: (%s)",
            images.size() +1,
            paths.size(),
            path
        );
        auto p_image = Image::LoadFromFile(path);
        images.push_back(p_image);
    }

    return images;
}
