//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : ImageSorters.h                                                //
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

//----------------------------------------------------------------------------//
// Export Headers                                                             //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
// Interfaces
#include "Interface/IImageSorter.h"

//------------------------------------------------------------------------------
// Implementations.
#include "Implementation/AreaImageSorter.h"
#include "Implementation/HeightImageSorter.h"
#include "Implementation/MaxSideImageSorter.h"
#include "Implementation/WidthImageSorter.h"

//------------------------------------------------------------------------------
// Factory
#include "Factory/ImageSorterFactory.h"