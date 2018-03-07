#pragma once

// TSP
#include "include/Core/ImageSorter/Interface/IImageSorter.h"

namespace TSP { namespace Core {

class WidthImageSorter :
    public IImageSorter
{
    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    virtual ~WidthImageSorter() = default;


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
        return pImg1->GetSize().width - pImg2->GetSize().width;
    }

}; // class WidthImageSorter

} // namespace Core
} // namespace TSP
