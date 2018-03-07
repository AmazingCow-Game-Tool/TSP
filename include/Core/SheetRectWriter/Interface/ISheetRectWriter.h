#pragma once

// AmazingCow Libs
#include "acow/cpp_goodies.h"
// TSP
#include "include/Core/Image/Images.h"

namespace TSP { namespace Core {

class ISheetRectWriter
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    ACOW_SMART_PTRS_OF(ISheetRectWriter);


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    virtual ~ISheetRectWriter() = default;


    //------------------------------------------------------------------------//
    // Interface Methods                                                      //
    //------------------------------------------------------------------------//
public:
    virtual void Write(
        const std::vector<Image::SPtr>      &images,
        const std::vector<acow::math::Rect> &rects,
        const acow::math::Size              &sheetSizeNeeded,
        bool                                 forcePOT,
        bool                                 forceSquare,
        const std::string                   &outputFullpath) const = 0;

}; // class ISheetRectWriter

} // namespace Core
} // namespace TSP
