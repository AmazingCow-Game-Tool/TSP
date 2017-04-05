#pragma once

//QT
#include <QtCore>
//TSP
#include "include/Image.h"

class IPackingStrategy
{
    // CTOR / DTOR //
public:
    virtual ~IPackingStrategy();


    // Interface Methods //
public:
    virtual void pack(const QVector<Image> &images) = 0;

    virtual const QVector<QRect>& getOutputRects() const = 0;

    virtual const QSize& getSheetSize() const = 0;
};
