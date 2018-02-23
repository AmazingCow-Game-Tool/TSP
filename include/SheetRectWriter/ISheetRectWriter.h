#pragma once

// TSP
#include "include/SheetWriterOptions/SheetWriterOptions.h"


class ISheetRectWriter
{
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

}; // ISheetRectWriter
