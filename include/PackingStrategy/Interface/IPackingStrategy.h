#pragma once

// std
#include <vector>
// AmazingCow Libs
#include "acow/math_goodies.h"
// TSP
#include "include/Image.h"


class IPackingStrategy
{
    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    virtual ~IPackingStrategy() = default;


    //------------------------------------------------------------------------//
    // Interface Methods                                                      //
    //------------------------------------------------------------------------//
public:
    virtual void Pack(const std::vector<Image> &images) noexcept = 0;

    virtual const std::vector<acow::math::Rect>& GetOutputRects() const noexcept = 0;

    virtual const acow::math::Size& GetSheetSize() const noexcept = 0;
};
