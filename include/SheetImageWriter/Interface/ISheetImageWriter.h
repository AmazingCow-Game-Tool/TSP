#pragma once

// TSP
#include "include/SheetWriterOptions/SheetWriterOptions.h"


class ISheetImageWriter
{
    // CTOR / DTOR //
public:
    virtual ~ISheetImageWriter() = default;


    // Interface Methods //
public:
    virtual void Write(const SheetWriterOptions &options) const = 0;
};
