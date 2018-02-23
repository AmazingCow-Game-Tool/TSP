#include <cstdlib>

#include "include/Packer.h"
#include "include/ImageFinder/ImageFinders.h"
#include "include/ImageLoader/ImageLoaders.h"
#include "include/PackingStrategy/PackingStrategies.h"
#include "include/PackerConstraint/PackerConstraints.h"
#include "include/SheetImageWriter/SheetImageWriters.h"
#include "include/SheetRectWriter/SheetRectWriters.h"


int main(int argc, char *argv[])
{
    //--------------------------------------------------------------------------
    // Image Finder.
    auto image_finder_options = DirectoryImageFinder::Options {
        .path_InitialPath = "~/Desktop/sprites",
        .path_IgnorePaths = {},
        .ext_Allowed      = {".png"}
    };

    auto p_image_finder = std::make_shared<DirectoryImageFinder>(
        image_finder_options
    );

    //--------------------------------------------------------------------------
    // Image Loader.
    auto p_image_loader = std::make_shared<ImageLoader>();

    //--------------------------------------------------------------------------
    // Images.
    auto images_list = p_image_loader->LoadImages(p_image_finder);

    auto p_packing_strategy   = std::make_unique<SimplePackingStrategy>();
    auto p_sheet_image_writer = std::make_unique<BasicSheetImageWriter>();
    auto p_sheet_rect_writer  = std::make_unique<CooperSheetRectWriter>();
    auto p_sort_method        = std::make_unique<AreaImageSorter>      ();


    //--------------------------------------------------------------------------
    // Packer.
    auto packer_options = Packer::Options {
        .sheet_ImageFilename = "test",
        .sheet_DataFilename  = "test",
        .sheet_OutputPath    = "~/Desktop/TestSheet"
    };

    auto packer = Packer(packer_options);

    packer.SetImages          (images_list               );
    packer.SetPackingMethod   (p_packing_strategy  .get());
    packer.SetSheetImageWriter(p_sheet_image_writer.get());
    packer.SetSheetRectWriter (p_sheet_rect_writer .get());
    packer.SetSortMethod      (p_sort_method       .get());

    packer.Pack();

    return EXIT_SUCCESS;
}
