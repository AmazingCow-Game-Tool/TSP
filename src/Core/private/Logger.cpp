//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Logger.cpp                                                    //
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
#include "include/Core/private/Logger.h"
// AmazingCow Libs
#include "acow/cpp_goodies.h"
// Usings
using namespace TSP;


//----------------------------------------------------------------------------//
// Functions                                                                  //
//----------------------------------------------------------------------------//
CoreLog::Logger*
Core::Logger() noexcept
{
    acow_local_persist std::unique_ptr<CoreLog::Logger> s_pLogger(nullptr);
    if(!s_pLogger)
        s_pLogger = acow::make_unique<CoreLog::Logger>();

    return s_pLogger.get();
}