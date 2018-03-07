#pragma once

// std
#include <string>
#include <vector>
// AmazingCow Libs
#include "acow/math_goodies.h"
// TSP
#include "include/Core/Image/Images.h"

namespace TSP { namespace Core {

struct SheetWriterOptions
{
    //--------------------------------------------------------------------------
    // Filenames.
    std::string filename_OutputImage;
    std::string filename_OutputData;

    //--------------------------------------------------------------------------
    // Path.
    std::string path_Output;

    //--------------------------------------------------------------------------
    // Size.
    acow::math::Size size_SheetNeeded;
    acow::math::Size size_SheetMin;
    acow::math::Size size_SheetMax;
    bool             size_ForcePOT;
    bool             size_ForceSquare;

    //--------------------------------------------------------------------------
    // Image
    bool     image_DebugDraw;
    bool     image_DebugRect;

}; // SheetWriterOptions

} // namespace Core
} // namespace TSP
