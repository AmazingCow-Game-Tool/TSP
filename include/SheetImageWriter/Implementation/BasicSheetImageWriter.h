#pragma once

// TSP
#include "include/SheetImageWriter/Interface/ISheetImageWriter.h"


class BasicSheetImageWriter :
    public ISheetImageWriter
{
    //------------------------------------------------------------------------//
    // Interface Methods                                                      //
    //------------------------------------------------------------------------//
public:
    void Write(const SheetWriterOptions &options) const noexcept override;

}; // class BasicSheetImageWriter
