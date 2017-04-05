#pragma once

//QT
#include <QtCore>
//TSP
#include "include/Image.h"


class ISheetRectWritter
{
    // CTOR / DTOR //
public:
    virtual ~ISheetRectWritter();

    // Interface Methods //
public:
    virtual void write(
        const QVector<Image> &images,
        const QVector<QRect> &rects,
        const QSize          &size
    ) const = 0;
};
