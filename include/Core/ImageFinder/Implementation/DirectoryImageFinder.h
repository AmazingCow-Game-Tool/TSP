//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : DirectoryImageFinder.h                                        //
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