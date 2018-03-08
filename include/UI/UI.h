//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : UI.h                                                          //
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

// AmazingCow Libs
#include "acow/sdl_goodies.h"
// TSP
#include "include/Core/RunInfo.h"


namespace TSP {

// "class-like" namespace
namespace UI
{
    //------------------------------------------------------------------------//
    // Init / Shutdown                                                        //
    //------------------------------------------------------------------------//
    void InitLean();

    void Init(const Core::RunInfo &runInfo) noexcept;
    void Shutdown() noexcept;


    //------------------------------------------------------------------------//
    // Lifecycle                                                              //
    //------------------------------------------------------------------------//
    void Run() noexcept;

    //------------------------------------------------------------------------//
    // Helper Functions                                                       //
    //------------------------------------------------------------------------//
    SDL_Renderer* GetRendererRef() noexcept;


}  // namespace UI

}  // namespace TSP