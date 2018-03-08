//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : ImageLoader.h                                                 //
//  Project   : TSP                                                           //
//  Date      : Mar 07, 2018                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2018                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

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
    Image::SPtr LoadImage(const std::string &path) override;

    std::vector<Image::SPtr> LoadImages(
        const std::vector<std::string> &paths) override;

}; // class ImageLoader

} // namespace Core
} // namespace TSP
