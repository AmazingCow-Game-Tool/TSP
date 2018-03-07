#pragma once

//----------------------------------------------------------------------------//
// Export Headers                                                             //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
// Interfaces
#include "Interface/IImageSorter.h"

//------------------------------------------------------------------------------
// Implementations.
#include "Implementation/AreaImageSorter.h"
#include "Implementation/HeightImageSorter.h"
#include "Implementation/MaxSideImageSorter.h"
#include "Implementation/WidthImageSorter.h"

//------------------------------------------------------------------------------
// Factory
#include "Factory/ImageSorterFactory.h"