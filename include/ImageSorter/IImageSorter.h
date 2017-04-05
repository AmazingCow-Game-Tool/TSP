#pragma once

//TSP
#include "include/Image.h"

class IImageSorter
{
    // CTOR / DTOR //
public:
    virtual ~IImageSorter();

    // Interface Methods //
public:
    virtual int sort(const Image &img1, const Image &img2) const = 0;
};

