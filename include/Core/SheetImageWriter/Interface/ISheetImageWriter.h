#pragma once

// AmazingCow Libs
#include "acow/cpp_goodies.h"
// TSP
#include "include/Core/SheetWriterOptions/SheetWriterOptions.h"


namespace TSP { namespace Core {

class ISheetImageWriter
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    ACOW_SMART_PTRS_OF(ISheetImageWriter);


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    virtual ~ISheetImageWriter() = default;


    //------------------------------------------------------------------------//
    // Interface Methods                                                      //
    //------------------------------------------------------------------------//
public:
    virtual void Write(
        const std::vector<Image::SPtr>      &images,
        const std::vector<acow::math::Rect> &rects,
        const SheetWriterOptions            &options) const = 0;

}; // class ISheetImageWriter

} // namespace Core
} // namespace TSP
