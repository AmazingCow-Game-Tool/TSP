//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : ImageSorterFactory.h                                          //
//  Project   : TSP                                                           //
//  Date      : Mar 07, 2018                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2018                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

#pragma mark
// std
#include <string>
// AmazingCow Libs
#include "acow/cpp_goodies.h"
// TSP
#include "include/Core/ImageSorter/Interface/IImageSorter.h"

namespace TSP { namespace Core {

// "class-like" namespace
namespace ImageSorterFactory
{
    //------------------------------------------------------------------------//
    // Create                                                                 //
    //------------------------------------------------------------------------//
    IImageSorter::UPtr CreateUnique(const std::string &name) noexcept;

} // namespace ImageSorterFactory

} // namespace Core
} // namespace TSP
