// AmazingCow Libs
#include "acow/cpp_goodies.h"
#include "CMD/CMD.h"
// TSP
#include "include/TSP.h"

// #include "include/Packer.h"
// #include "include/ImageFinder/ImageFinders.h"
// #include "include/ImageLoader/ImageLoaders.h"
// #include "include/PackingStrategy/PackingStrategies.h"
// #include "include/PackerConstraint/PackerConstraints.h"
// #include "include/SheetImageWriter/SheetImageWriters.h"
// #include "include/SheetRectWriter/SheetRectWriters.h"


//----------------------------------------------------------------------------//
// Helper Functions                                                           //
//----------------------------------------------------------------------------//
acow_internal_function void
show_help(const std::string &help_msg) noexcept
{
    printf("%s", help_msg.c_str());

    ACOW_DEBUGGER_BREAK();
    exit(0);
}

acow_internal_function void
show_version() noexcept
{
    printf("Version\n");
    exit(0);
}

acow_internal_function TSP::Core::RunInfo
parse_cmd_line(int argc, char *argv[])
{
     //--------------------------------------------------------------------------
    // Help / Version
    auto flag_help    = CMD::Flag::Create(
        "h",
        "help",
        "Show this screen.",
        CMD::StopOnView
    );

    auto flag_version = CMD::Flag::Create(
        "v",
        "version",
        "Show version and copyright.",
        CMD::StopOnView
    );

    //--------------------------------------------------------------------------
    // Directories.
    auto flag_images_dir = CMD::Flag::Create(
        "",
        "images-dir",
        "Add image directory.",
        CMD::RequiredArgument | CMD::AllowDuplicates | CMD::MergeArgument
    );

    auto flag_output_dir = CMD::Flag::Create(
        "o",
        "output-dir",
        "Directory where sheet will be placed.",
        CMD::RequiredArgument | CMD::NoDuplicates
    );
    //----------------------------------------------------------------------
    // Sheet Info.
    auto flag_sheet_image_name = CMD::Flag::Create(
        "",
        "sheet-image-name",
        "The filename of resulting sheet image.",
        CMD::RequiredArgument | CMD::NoDuplicates
    );
    auto flag_sheet_data_name = CMD::Flag::Create(
        "",
        "sheet-data-name",
        "The filename of resulting sheet data.",
        CMD::RequiredArgument | CMD::NoDuplicates
    );
    auto flag_sheet_image_format = CMD::Flag::Create(
        "",
        "sheet-image-format",
        "The image format of the resulting sheet image.",
        CMD::RequiredArgument | CMD::NoDuplicates
    );
    auto flag_sheet_data_format = CMD::Flag::Create(
        "",
        "sheet-data-format",
        "The data format of the resulting sheet image.",
        CMD::RequiredArgument | CMD::NoDuplicates
    );
    auto flag_debug_images = CMD::Flag::Create(
        "",
        "debug-images",
        "Output images will contain a color overly to ease debug.",
        CMD::AllowDuplicates
    );
    //----------------------------------------------------------------------
    // GUI
    auto flag_gui = CMD::Flag::Create(
        "",
        "gui",
        "Open the program in GUI mode.",
        CMD::AllowDuplicates
    );

    //--------------------------------------------------------------------------
    // Parse.
    auto cmd = CMD::Parser(
        CMD::DieOnNonValidFlags,
        {
            flag_help,
            flag_version,
            flag_images_dir,
            flag_output_dir,
            flag_sheet_image_name,
            flag_sheet_data_name,
            flag_sheet_image_format,
            flag_sheet_data_format,
            flag_debug_images,
            flag_gui
        }
    ).Parse(argc, argv);


    TSP::Core::RunInfo run_info;

    //--------------------------------------------------------------------------
    // Help Version.
    if(flag_help   ->Found()) show_help(cmd.GenerateHelpString());
    if(flag_version->Found()) show_version();

    //--------------------------------------------------------------------------
    // Directories
    if(flag_images_dir->Found()) run_info.dirs_Images = flag_images_dir->GetValues();
    if(flag_output_dir->Found()) run_info.dir_Output  = flag_output_dir->GetValue ();

    //--------------------------------------------------------------------------
    // Sheet Info.
    if(flag_sheet_image_name->Found())
        run_info.sheet_ImageName = flag_sheet_image_name->GetValue();

    if(flag_sheet_data_name->Found())
        run_info.sheet_DataName = flag_sheet_data_name->GetValue();

    if(flag_sheet_image_format->Found())
        run_info.sheet_ImageFormat = flag_sheet_image_format->GetValue();

    if(flag_sheet_data_format->Found())
        run_info.sheet_DataFormat = flag_sheet_data_format->GetValue();

    if(flag_debug_images->Found())
        run_info.debug_Image = true;

    //--------------------------------------------------------------------------
    // GUI
    if(flag_gui->Found())
        run_info.gui_Enabled = true;

    return run_info;
}



//----------------------------------------------------------------------------//
// Entry Point                                                                //
//----------------------------------------------------------------------------//
int main(int argc, char *argv[])
{
    auto run_info = parse_cmd_line(argc, argv);

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
