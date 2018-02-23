#pragma once

// AmazingCow Libs
#include "acow/cpp_goodies.h"
// TSP
#include "include/SheetWriterOptions/SheetWriterOptions.h"


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
    virtual void Write(const SheetWriterOptions &options) const = 0;

}; // class ISheetRectWriter
