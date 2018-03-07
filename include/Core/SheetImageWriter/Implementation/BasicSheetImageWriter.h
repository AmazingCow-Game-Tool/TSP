#pragma once

// TSP
#include "include/Core/SheetImageWriter/Interface/ISheetImageWriter.h"

namespace TSP { namespace Core {

class BasicSheetImageWriter :
    public ISheetImageWriter
{
    //------------------------------------------------------------------------//
    // Interface Methods                                                      //
    //------------------------------------------------------------------------//
public:
    void Write(
        const std::vector<Image::SPtr>      &images,
        const std::vector<acow::math::Rect> &rects,
        const SheetWriterOptions            &options) const noexcept override;

}; // class BasicSheetImageWriter

} // namespace Core
} // namespace TSP
