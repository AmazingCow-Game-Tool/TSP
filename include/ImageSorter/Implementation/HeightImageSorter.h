#pragma once

// TSP
#include "include/ImageSorter/Interface/IImageSorter.h"

class HeightImageSorter :
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
        return pImg1->GetSize().height - pImg2->GetSize().height;
    }

}; // class HeightImageSorter
