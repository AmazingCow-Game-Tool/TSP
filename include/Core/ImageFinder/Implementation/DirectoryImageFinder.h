#pragma once

// TSP
#include "include/Core/ImageFinder/Interface/IImageFinder.h"

namespace TSP { namespace Core {

class DirectoryImageFinder
    : public IImageFinder
{
    //------------------------------------------------------------------------//
    // Inner Types                                                            //
    //------------------------------------------------------------------------//
public:
    struct Options
    {
        // Path.
        std::string              path_InitialPath;
        std::vector<std::string> path_IgnorePaths;

        // Extension.
        std::vector<std::string> ext_Allowed;

    }; // struct Options;


    //------------------------------------------------------------------------//
    // CTOR                                                                   //
    //------------------------------------------------------------------------//
public:
    explicit DirectoryImageFinder(const Options &options) noexcept;


    //------------------------------------------------------------------------//
    // Interface Methods                                                      //
    //------------------------------------------------------------------------//
public:
    std::vector<std::string> FindImagesPaths() override;


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    Options                  m_options;
    std::vector<std::string> m_imagePaths;

}; // class ImageFinder

} // namespace Core
} // namespace TSP