// AmazingCow Libs
#include "acow/cpp_goodies.h"
#include "CMD/CMD.h"
// TSP
#include "include/TSP.h"



//----------------------------------------------------------------------------//
// Entry Point                                                                //
//----------------------------------------------------------------------------//
int main(int argc, char *argv[])
{
    using namespace TSP;

    auto run_info = Core::ParseCommandLine(argc, argv);

    if(run_info.gui_Enabled)
    {
        TSP::UI::Init(run_info);
        TSP::UI::Run();
        TSP::UI::Shutdown();
    }
    else
    {
        //----------------------------------------------------------------------
        // Image Finder.
        auto image_finder_options = TSP::Core::DirectoryImageFinder::Options {
            .path_InitialPath = "~/Desktop/sprites",
            .path_IgnorePaths = {},
            .ext_Allowed      = {".png"}
        };

        auto p_image_finder = std::make_shared<TSP::Core::DirectoryImageFinder>(
            image_finder_options
        );
    }
}





//     //--------------------------------------------------------------------------
//     // Image Loader.
//     auto p_image_loader = std::make_shared<ImageLoader>();

//     //--------------------------------------------------------------------------
//     // Images.
//     auto images_list = p_image_loader->LoadImages(p_image_finder);
//     auto p_packing_strategy   = acow::make_unique<SimplePackingStrategy>();
//     auto p_sheet_image_writer = acow::make_unique<BasicSheetImageWriter>();
//     auto p_sheet_rect_writer  = acow::make_unique<CooperSheetRectWriter>();
//     auto p_sort_method        = acow::make_unique<WidthImageSorter>      ();

//     //--------------------------------------------------------------------------
//     // Packer.
//     auto packer_options = Packer::Options {
//         .sheet_ImageFilename = "test",
//         .sheet_DataFilename  = "test",
//         .sheet_OutputPath    = "~/Desktop/TestSheet"
//     };

//     auto packer = Packer(packer_options);
//     packer.SetImages          (images_list               );
//     packer.SetPackingMethod   (p_packing_strategy  .get());
//     packer.SetSheetImageWriter(p_sheet_image_writer.get());
//     packer.SetSheetRectWriter (p_sheet_rect_writer .get());
//     packer.SetSortMethod      (p_sort_method       .get());
//     packer.Pack();

//     return EXIT_SUCCESS;
// }
