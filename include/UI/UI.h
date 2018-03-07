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