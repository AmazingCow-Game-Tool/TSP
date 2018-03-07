#pragma once

// TSP
#include "include/Core/SheetRectWriter/Interface/ISheetRectWriter.h"
#include "include/Core/Image/Images.h"

namespace TSP { namespace Core {

class CooperSheetRectWriter
    : public ISheetRectWriter
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    ACOW_SMART_PTRS_OF(CooperSheetRectWriter);


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    virtual ~CooperSheetRectWriter() = default;


    //------------------------------------------------------------------------//
    // Interface Methods                                                      //
    //------------------------------------------------------------------------//
public:
    void Write(
        const std::vector<Image::SPtr>      &images,
        const std::vector<acow::math::Rect> &rects,
        const acow::math::Size              &sheetSizeNeeded,
        bool                                 forcePOT,
        bool                                 forceSquare,
        const std::string                   &outputFullpath) const override;

}; // class CooperSheetSheetRectWriter

} // namespace Core
} // namespace TSP
