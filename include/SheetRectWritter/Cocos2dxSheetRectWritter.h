#pragma once

//QT
#include <QtCore>
//TSP
#include "include/SheetRectWritter/ISheetRectWritter.h"


class Cocos2dxSheetRectWritter :
    public ISheetRectWritter
{
    // Interface Methods //
public:
    virtual void write(const SheetWritterOptions &options) const override;
};
