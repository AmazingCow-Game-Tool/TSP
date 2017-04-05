#pragma once

//QT
#include <QtCore>
//TSP
#include "include/Image.h"


class ISheetImageWritter
{
    // CTOR / DTOR //
public:
    virtual ~ISheetImageWritter();

    // Interface Methods //
public:
    virtual void write(
        const QVector<Image> &images,
        const QVector<QRect> &rects,
        const QSize          &size
    ) const = 0;
};
