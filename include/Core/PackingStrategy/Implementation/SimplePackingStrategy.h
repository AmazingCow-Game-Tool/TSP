#pragma once

// std
#include <vector>
// AmazingCow Libs
#include "acow/cpp_goodies.h"
#include "acow/math_goodies.h"
// TSP
#include "include/Core/PackingStrategy/Interface/IPackingStrategy.h"

namespace TSP { namespace Core {

class SimplePackingStrategy :
    public IPackingStrategy
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    ACOW_SMART_PTRS_OF(SimplePackingStrategy);


    //------------------------------------------------------------------------//
    // Interface Methods                                                      //
    //------------------------------------------------------------------------//
public:
    PackResults Pack(const std::vector<Image::SPtr> &images) noexcept override;

}; // class SimplePackingStrategy

} // namespace Core
} // namespace TSP
