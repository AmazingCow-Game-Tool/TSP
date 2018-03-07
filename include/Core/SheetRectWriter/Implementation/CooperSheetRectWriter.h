#pragma once

// TSP
#include "include/Core/SheetRectWriter/Interface/ISheetRectWriter.h"

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
    void Write(const SheetWriterOptions &options) const override;

}; // class CooperSheetSheetRectWriter

} // namespace Core
} // namespace TSP
