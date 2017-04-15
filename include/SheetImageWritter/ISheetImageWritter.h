#pragma once

//QT
#include <QtCore>
//TSP
#include "include/SheetWritterOptions/SheetWritterOptions.h"


class ISheetImageWritter
{
    // CTOR / DTOR //
public:
    virtual ~ISheetImageWritter();

    // Interface Methods //
public:
    virtual void write(const SheetWritterOptions &options) const = 0;
};
