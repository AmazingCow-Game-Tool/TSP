#pragma once

//QT
#include <QtCore>
//TSP
#include "include/SheetWritterOptions/SheetWritterOptions.h"


class ISheetRectWritter
{
    // CTOR / DTOR //
public:
    virtual ~ISheetRectWritter();

    // Interface Methods //
public:
    virtual void write(const SheetWritterOptions &options) const = 0;
};
