// Header
#include "include/Core/SheetRectWriter/Implementation/CooperSheetRectWriter.h"
// AmazingCow Libs
#include "CoreIni/CoreIni.h"
#include "CoreString/CoreString.h"
#include "CoreFS/CoreFS.h"

// Usings
using namespace TSP;
using namespace Core;


//----------------------------------------------------------------------------//
// Interface Methods                                                          //
//----------------------------------------------------------------------------//
void
CooperSheetRectWriter::Write(
    const std::vector<Image::SPtr>      &images,
    const std::vector<acow::math::Rect> &rects,
    const acow::math::Size              &sheetSizeNeeded,
    bool                                 forcePOT,
    bool                                 forceSquare,
    const std::string                   &outputFullpath) const
{
    // CoreIni::Ini ini;

    // ini.AddSection("Texture");
    // ini.AddValue("Texture", "Name", options.imageOutputFilename);

    // ini.AddSection("Rects");
    // for(int i = 0; i < options.images.size(); ++i)
    // {
    //     const auto image = options.images[i];
    //     const auto rect  = options.rects [i];

    //     ini.AddValue(
    //         "Rects",
    //         image->GetBasename(),
    //         CoreString::Format(
    //             "%.2f %.2f %.2f %2f",
    //             rect.x,
    //             rect.y,
    //             rect.GetWidth(),
    //             rect.GetHeight()
    //         )
    //     );
    // }

    // auto a = 10;
    // ini.Save(
    //     CoreFS::Join(options.outputPath, {options.dataOutputFilename})
    // );

}
