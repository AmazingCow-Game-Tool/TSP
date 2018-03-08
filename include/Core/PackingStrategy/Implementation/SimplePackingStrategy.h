//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : SimplePackingStrategy.h                                       //
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
// AmazingCow Libs
#include "acow/cpp_goodies.h"
#include "acow/math_goodies.h"
// TSP
#include "include/Core/PackingStrategy/Interface/IPackingStrategy.h"

namespace TSP { namespace Core {

class SimplePackingStrategy :
    public IPackingStrategy
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    ACOW_SMART_PTRS_OF(SimplePackingStrategy);


    //------------------------------------------------------------------------//
    // Interface Methods                                                      //
    //------------------------------------------------------------------------//
public:
    PackResults Pack(const std::vector<Image::SPtr> &images) noexcept override;

}; // class SimplePackingStrategy

} // namespace Core
} // namespace TSP
