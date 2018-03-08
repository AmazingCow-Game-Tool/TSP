//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : IImageFinder.h                                                //
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
#include <string>
#include <vector>
// AmazingCow Libs
#include "acow/cpp_goodies.h"

namespace TSP { namespace Core {

class IImageFinder
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedef                                            //
    //------------------------------------------------------------------------//
public:
    ACOW_SMART_PTRS_OF(IImageFinder);


    //------------------------------------------------------------------------//
    // Interface Methods                                                      //
    //------------------------------------------------------------------------//
public:
    virtual std::vector<std::string> FindImagesPaths() = 0;

}; // class IImageFinder

} // namespace Core
} // namespace TSP
