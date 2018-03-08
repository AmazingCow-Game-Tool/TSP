// Header
#include "include/Core/ImageSorter/Factory/ImageSorterFactory.h"
// AmazingCow Libs
#include "CoreAssert/CoreAssert.h"
#include "CoreString/CoreString.h"
// TSP
#include "include/Core/ImageSorter/Implementation/AreaImageSorter.h"
#include "include/Core/ImageSorter/Implementation/HeightImageSorter.h"
#include "include/Core/ImageSorter/Implementation/MaxSideImageSorter.h"
#include "include/Core/ImageSorter/Implementation/WidthImageSorter.h"

// Usings
using namespace TSP;
using namespace Core;


//----------------------------------------------------------------------------//
// Create                                                                     //
//----------------------------------------------------------------------------//
IImageSorter::UPtr
ImageSorterFactory::CreateUnique(const std::string &name) noexcept
{
    COREASSERT_ASSERT(!name.empty(), "name can't be empty.");
    auto lower_name = CoreString::ToLower(name);

    if     (lower_name == "area"   ) return acow::make_unique<AreaImageSorter   >();
    else if(lower_name == "height" ) return acow::make_unique<HeightImageSorter >();
    else if(lower_name == "maxside") return acow::make_unique<MaxSideImageSorter>();
    else if(lower_name == "width"  ) return acow::make_unique<WidthImageSorter  >();

    COREASSERT_ASSERT(false, "Invalid image sorter - name: (%s)", name.c_str());
    return nullptr; // Just to make compiler happy...
}
