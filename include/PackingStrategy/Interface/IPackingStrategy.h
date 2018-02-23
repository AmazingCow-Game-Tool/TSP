#pragma once

// std
#include <vector>
// AmazingCow Libs
#include "acow/math_goodies.h"
// TSP
#include "include/Image/Images.h"


class IPackingStrategy
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    ACOW_SMART_PTRS_OF(IPackingStrategy);


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    virtual ~IPackingStrategy() = default;


    //------------------------------------------------------------------------//
    // Interface Methods                                                      //
    //------------------------------------------------------------------------//
public:
    virtual void Pack(const std::vector<Image::SPtr> &images) noexcept = 0;

    virtual const std::vector<acow::math::Rect>& GetOutputRects() const noexcept = 0;

    virtual const acow::math::Size& GetSheetSize() const noexcept = 0;
};
