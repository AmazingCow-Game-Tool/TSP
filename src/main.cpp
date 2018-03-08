//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : main.cpp                                                      //
//  Project   : TSP                                                           //
//  Date      : Apr 04, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017, 2018                                       //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// std
#include <string>
#include <vector>
#include <algorithm>
// AmazingCow Libs
#include "acow/cpp_goodies.h"
#include "CMD/CMD.h"
#include "CoreFS/CoreFS.h"
#include "CoreDir/CoreDir.h"
// TSP
#include "include/TSP.h"

//----------------------------------------------------------------------------//
// Entry Point                                                                //
//----------------------------------------------------------------------------//
int main(int argc, char *argv[])
{
    using namespace TSP;

    auto run_info = Core::ParseCommandLine(argc, argv);
    run_info.gui_Enabled    = true;
    run_info.sheet_ForcePOT = true;

    if(run_info.gui_Enabled)
    {
        UI::Init(run_info);
        UI::Run ();
    }
    else
    {
    //     //----------------------------------------------------------------------
    //     // Find / Load the images.
    //     auto image_finder = Core::DirectoryImageFinder(
    //         run_info.dirs_Images,
    //         run_info.dirs_ImagesAllowedExtensions
    //     );
    //     auto images_paths = image_finder.FindImagesPaths();

    //     auto images_loader = Core::ImageLoader();
    //     auto images_list   = images_loader.LoadImages(images_paths);



    //     //----------------------------------------------------------------------
    //     // Pack.
    //     auto p_packing_strategy  = ;
    //     auto packing_results = p_packing_strategy->Pack(images_list);

    //     //----------------------------------------------------------------------
    //     // Save results.
    //     auto p_sheet_image_writer = acow::make_unique<Core::BasicSheetImageWriter>();
    //     auto p_sheet_rect_writer  = acow::make_unique<Core::CooperSheetRectWriter>();

    //     auto image_filename = CoreFS::ChangeExtension(
    //         run_info.sheet_ImageName,
    //         run_info.sheet_ImageFormat
    //     );

    //     auto outpath = CoreFS::ExpandUserAndMakeAbs(run_info.dir_Output);
    //     CoreDir::CreateDirectory(outpath); // no-op if already exists.

    //     auto image_fullpath = CoreFS::Join(outpath, {image_filename});

    //     p_sheet_image_writer->Write(
    //         images_list,
    //         packing_results.rects,
    //         packing_results.sheet_Size,
    //         run_info.sheet_ForcePOT,
    //         run_info.sheet_ForceSquare,
    //         image_fullpath
    //     );
    }

    UI::Shutdown();
}









//     //--------------------------------------------------------------------------
//     // Packer.
//     auto packer_options = Packer::Options {
//         .sheet_ImageFilename = "test",
//         .sheet_DataFilename  = "test",
//         .sheet_OutputPath    = "~/Desktop/TestSheet"
//     };

//     packer.SetImages          (images_list               );
//     packer.SetPackingMethod   (p_packing_strategy  .get());
//     packer.SetSheetImageWriter(p_sheet_image_writer.get());
//     packer.SetSheetRectWriter (p_sheet_rect_writer .get());
//     packer.SetSortMethod      (p_sort_method       .get());
//     ;

//     return EXIT_SUCCESS;
// }
