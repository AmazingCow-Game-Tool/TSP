#pragma once

// std
#include <string>
#include <vector>

class ImageFinder
{
    //------------------------------------------------------------------------//
    // Inner Types                                                            //
    //------------------------------------------------------------------------//
public:
    struct Options
    {
        std::string              startPath;
        std::vector<std::string> ignorePaths;
        std::vector<std::string> allowedFiletypes;
    };


    //------------------------------------------------------------------------//
    // CTOR                                                                   //
    //------------------------------------------------------------------------//
public:
    ImageFinder(const Options &options);


    //------------------------------------------------------------------------//
    // Public Methods                                                         //
    //------------------------------------------------------------------------//
public:
    std::vector<std::string> findImagesPaths();


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    Options                  m_options;
    std::vector<std::string> m_imagePaths;
};
