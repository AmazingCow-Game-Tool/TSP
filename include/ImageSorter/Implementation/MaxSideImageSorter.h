#pragma once

// std
#include <algorithm>
// TSP
#include "include/ImageSorter/Interface/IImageSorter.h"

class MaxSideImageSorter :
    public IImageSorter
{
    //------------------------------------------------------------------------//
    // Interface Methods                                                      //
    //------------------------------------------------------------------------//
public:
      int Sort(
        const Image::SPtr &pImg1,
        const Image::SPtr &pImg2) const noexcept override
    {
        // Sanity Checks.
        COREASSERT_ASSERT(pImg1, "pImg1 can't be null");
        COREASSERT_ASSERT(pImg2, "pImg2 can't be null");

        // Implementation.
        auto &s1 = pImg1->GetSize();
        auto &s2 = pImg2->GetSize();

        return std::max(s1.width, s1.height) -
               std::max(s2.width, s2.height);
    }

}; // class MaxSideImageSorter
