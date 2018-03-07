#pragma once

// std
#include <string>
#include <vector>
// AmazingCow Libs
#include "acow/cpp_goodies.h"

namespace TSP { namespace Core {

class IImageFinder
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedef                                            //
    //------------------------------------------------------------------------//
public:
    ACOW_SMART_PTRS_OF(IImageFinder);


    //------------------------------------------------------------------------//
    // Interface Methods                                                      //
    //------------------------------------------------------------------------//
public:
    virtual std::vector<std::string> FindImagesPaths() noexcept = 0;

}; // class IImageFinder

} // namespace Core
} // namespace TSP
