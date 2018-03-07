#pragma mark
// std
#include <string>
// TSP
#include "include/Core/ImageSorter/Interface/IImageSorter.h"

namespace TSP { namespace Core {

// "class-like" namespace
namespace ImageSorterFactory
{
    //------------------------------------------------------------------------//
    // Create                                                                 //
    //------------------------------------------------------------------------//
    IImageSorter::UPtr CreateUnique(const std::string &name) noexcept;

} // namespace ImageSorterFactory

} // namespace Core
} // namespace TSP
