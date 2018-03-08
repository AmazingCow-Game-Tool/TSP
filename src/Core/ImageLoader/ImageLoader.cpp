//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : ImageLoader.cpp                                               //
//  Project   : TSP                                                           //
//  Date      : Mar 07, 2018                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2018                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

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
Image::SPtr
ImageLoader::LoadImage(const std::string &path)
{
    return Image::LoadFromFile(path);
}

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
        images.push_back(LoadImage(path));
    }

    return images;
}
