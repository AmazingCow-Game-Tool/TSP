#pragma once

// std
#include <vector>
#include <string>
// TSP
#include "include/Core/ImageFinder/Interface/IImageFinder.h"

namespace TSP { namespace Core {

class DirectoryImageFinder
    : public IImageFinder
{
    //------------------------------------------------------------------------//
    // CTOR                                                                   //
    //------------------------------------------------------------------------//
public:
    DirectoryImageFinder(
        const std::vector<std::string> &initialPaths,
        const std::vector<std::string> &allowedExtentions);


    //------------------------------------------------------------------------//
    // Interface Methods                                                      //
    //------------------------------------------------------------------------//
public:
    std::vector<std::string> FindImagesPaths() override;


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    std::vector<std::string> m_initialPaths;
    std::vector<std::string> m_allowedExtensions;

}; // class ImageFinder

} // namespace Core
} // namespace TSP