#pragma once

//QT
#include <QtCore>
//TSP
#include "include/SheetImageWritter/ISheetImageWritter.h"


class BasicSheetImageWritter :
    public ISheetImageWritter
{
    // Interface Methods //
public:
    virtual void write(const SheetWritterOptions &options) const override;
};
