//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : RunInfo.h                                                     //
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
#include "acow/math_goodies.h"

namespace TSP { namespace Core {

//----------------------------------------------------------------------------//
// Types                                                                      //
//----------------------------------------------------------------------------//
struct RunInfo
{
    // Directories.
    std::vector<std::string> dirs_Images;
    std::vector<std::string> dirs_ImagesAllowedExtensions;
    std::string              dir_Output;

    // Image Info.
    std::string      sheet_ImageName;
    std::string      sheet_ImageFormat;
    bool             sheet_ImageDebug;
    acow::math::Size sheet_SizeMin;
    acow::math::Size sheet_SizeMax;
    bool             sheet_ForcePOT;
    bool             sheet_ForceSquare;

    // Data Info.
    std::string sheet_DataName;
    std::string sheet_DataFormat;

    // Pack.
    std::string pack_SortType;

    // GUI.
    bool gui_Enabled;

}; // struct RunInfo


//----------------------------------------------------------------------------//
// Functions                                                                  //
//----------------------------------------------------------------------------//
RunInfo ParseCommandLine(int argc, char *argv[]);

}  // namespace Core
}  // namespace TSP
