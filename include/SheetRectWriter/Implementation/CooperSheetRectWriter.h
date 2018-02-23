#pragma once

// TSP
#include "include/SheetRectWriter/Interface/ISheetRectWriter.h"


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
