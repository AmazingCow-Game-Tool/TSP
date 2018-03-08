//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : RunInfo.cpp                                                   //
//  Project   : TSP                                                           //
//  Date      : Mar 07, 2018                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2018                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// Header
#include "include/Core/RunInfo.h"
// AmazingCow Libs
#include "acow/cpp_goodies.h"
#include "acow/algo.h"
#include "CMD/CMD.h"
#include "CoreString/CoreString.h"
#include "CoreAssert/CoreAssert.h"
#include "CoreFS/CoreFS.h"

// Usings
using namespace CMD;
using namespace TSP;

//----------------------------------------------------------------------------//
// Internal Vars                                                              //
//----------------------------------------------------------------------------//
// Help
acow_global_variable Flag::SPtr g_pFlagHelp    = nullptr;
acow_global_variable Flag::SPtr g_pFlagVersion = nullptr;
// Directories.
acow_global_variable Flag::SPtr g_pFlagDirsImages    = nullptr;
acow_global_variable Flag::SPtr g_pFlagDirAllowedExt = nullptr;
acow_global_variable Flag::SPtr g_pFlagDirOutput     = nullptr;
// Sheet Image Info.
acow_global_variable Flag::SPtr g_pFlagSheetImageName       = nullptr;
acow_global_variable Flag::SPtr g_pFlagSheetImageFormat     = nullptr;
acow_global_variable Flag::SPtr g_pFlagSheetImageDebug      = nullptr;
acow_global_variable Flag::SPtr g_pFlagSheetSizeMin         = nullptr;
acow_global_variable Flag::SPtr g_pFlagSheetSizeMax         = nullptr;
acow_global_variable Flag::SPtr g_pFlagSheetSizeForcePOT    = nullptr;
acow_global_variable Flag::SPtr g_pFlagSheetSizeForceSquare = nullptr;
// Sheet Data Info.
acow_global_variable Flag::SPtr g_pFlagSheetDataName   = nullptr;
acow_global_variable Flag::SPtr g_pFlagSheetDataFormat = nullptr;
// Pack.
acow_global_variable Flag::SPtr g_pFlagPackSortType = nullptr;
// GUI.
acow_global_variable Flag::SPtr g_pFlagGUI = nullptr;


//----------------------------------------------------------------------------//
// Helper Functions                                                           //
//----------------------------------------------------------------------------//
acow_internal_function inline void
show_help(const std::string &help_msg) noexcept
{
    printf("%s", help_msg.c_str());

    ACOW_DEBUGGER_BREAK();
    exit(0);
}

acow_internal_function inline void
show_version() noexcept
{
    printf("Version\n");
    exit(0);
}

acow_internal_function inline acow::math::Size
parse_size_from_str(const std::string &str)
{
    int w, h;
    auto filled = sscanf(str.c_str(), "%d?%d", &w, &h);

    COREASSERT_THROW_IF(
        filled != 2,
        std::invalid_argument,
        "size isn't in the correct format (Width)x(Height) - Found(%s)",
        str.c_str()
    );

    return acow::math::Size(w, h);
}

//----------------------------------------------------------------------------//
// Init Functions                                                             //
//----------------------------------------------------------------------------//
acow_internal_function inline void
init_group_help(Parser *pParser) noexcept
{
    COREASSERT_ASSERT(pParser, "pParser can't be null");

    auto group_name = "General";

    // Help.
    g_pFlagHelp = Flag::Create(
        "h",
        "help",
        "Show this screen.",
        CMD::StopOnView,
        group_name
    );
    pParser->AddFlag(g_pFlagHelp);

    // Version.
    g_pFlagVersion = Flag::Create(
        "v",
        "version",
        "Show version and copyright.",
        CMD::StopOnView,
        group_name
    );
    pParser->AddFlag(g_pFlagVersion);
}

acow_internal_function inline void
init_group_directories(Parser *pParser) noexcept
{
    COREASSERT_ASSERT(pParser, "pParser can't be null");

    auto group_name = "Directories";

    // Images Dir.
    g_pFlagDirsImages = Flag::Create(
        "",
        "dir-images",
        "Add image directory.",
        CMD::RequiredArgument | CMD::AllowDuplicates | CMD::MergeArgument,
        group_name
    );
    pParser->AddFlag(g_pFlagDirsImages);

    // Allowed Ext.
    g_pFlagDirAllowedExt = Flag::Create(
        "",
        "dir-allowed-extensions",
        "Set the allowed extensions.",
        CMD::RequiredArgument | CMD::AllowDuplicates,
        group_name
    );
    pParser->AddFlag(g_pFlagDirAllowedExt);

    // Output Dir.
    g_pFlagDirOutput = Flag::Create(
        "o",
        "dir-output",
        "Directory where sheet will be placed.",
        CMD::RequiredArgument | CMD::NoDuplicates,
        group_name
    );
    pParser->AddFlag(g_pFlagDirOutput);
}

acow_internal_function inline void
init_group_image_info(Parser *pParser) noexcept
{
    COREASSERT_ASSERT(pParser, "pParser can't be null");

    auto group_name = "Image Info";

    // Image Name.
    g_pFlagSheetImageName = Flag::Create(
        "",
        "sheet-image-name",
        "The filename of resulting sheet image.",
        CMD::RequiredArgument | CMD::NoDuplicates,
        group_name
    );
    pParser->AddFlag(g_pFlagSheetImageName);

    // Image Format.
    g_pFlagSheetImageFormat = Flag::Create(
        "",
        "sheet-image-format",
        "The image format of the resulting sheet image.",
        CMD::RequiredArgument | CMD::NoDuplicates,
        group_name
    );
    pParser->AddFlag(g_pFlagSheetImageFormat);

    // Debug Images.
    g_pFlagSheetImageDebug = Flag::Create(
        "",
        "sheet-debug-images",
        "Output images will contain a color overly to ease debug.",
        CMD::AllowDuplicates,
        group_name
    );
    pParser->AddFlag(g_pFlagSheetImageDebug);

    // Sheet Size Min.
    g_pFlagSheetSizeMin = Flag::Create(
        "",
        "sheet-size-min",
        "Minimum size of the output image.",
        CMD::RequiredArgument | CMD::NoDuplicates,
        group_name
    );
    pParser->AddFlag(g_pFlagSheetSizeMin);

    // Sheet Size Max.
    g_pFlagSheetSizeMax = Flag::Create(
        "",
        "sheet-size-max",
        "Maximum size of the output image.",
        CMD::RequiredArgument | CMD::NoDuplicates,
        group_name
    );
    pParser->AddFlag(g_pFlagSheetSizeMax);

    // Size Force POT.
    g_pFlagSheetSizeForcePOT = Flag::Create(
        "",
        "sheet-force-pot",
        "COWTODO.",
        CMD::NoDuplicates,
        group_name
    );
    pParser->AddFlag(g_pFlagSheetSizeForcePOT);

    // Size Force Square.
    g_pFlagSheetSizeForceSquare = Flag::Create(
        "",
        "sheet-force-square",
        "COWTODO.",
        CMD::NoDuplicates,
        group_name
    );
    pParser->AddFlag(g_pFlagSheetSizeForceSquare);

    // COWTODO(n2omatt): Debug colors? (color - random)
}

acow_internal_function inline void
init_group_data_info(Parser *pParser) noexcept
{
    COREASSERT_ASSERT(pParser, "pParser can't be null");

    auto group_name = "Data Info";

    // Data Name.
    g_pFlagSheetDataName = Flag::Create(
        "",
        "sheet-data-name",
        "The filename of resulting sheet data.",
        CMD::RequiredArgument | CMD::NoDuplicates,
        group_name
    );
    pParser->AddFlag(g_pFlagSheetDataName);

    // Data Format.
    g_pFlagSheetDataFormat = Flag::Create(
        "",
        "sheet-data-format",
        "The data format of the resulting sheet image.",
        CMD::RequiredArgument | CMD::NoDuplicates,
        group_name
    );
    pParser->AddFlag(g_pFlagSheetDataFormat);
}

acow_internal_function inline void
init_group_pack(Parser *pParser) noexcept
{
    COREASSERT_ASSERT(pParser, "pParser can't be null");

    auto group_name = "Pack";

    // Sort Type.
    g_pFlagPackSortType = Flag::Create(
        "",
        "pack-sort-type",
        "How sort the images.",
        CMD::RequiredArgument,
        group_name
    );
    pParser->AddFlag(g_pFlagPackSortType);
}

acow_internal_function inline void
init_group_gui(Parser *pParser) noexcept
{
    COREASSERT_ASSERT(pParser, "pParser can't be null");

    auto group_name = "GUI";

    // GUI.
    g_pFlagGUI = Flag::Create(
        "",
        "gui",
        "Open the program in GUI mode.",
        CMD::AllowDuplicates,
        group_name
    );
    pParser->AddFlag(g_pFlagGUI);
}


//----------------------------------------------------------------------------//
// Get Results Functions                                                      //
//----------------------------------------------------------------------------//
acow_internal_function inline void
get_results_group_help(Core::RunInfo *pRunInfo, Parser *pParser) noexcept
{
    COREASSERT_ASSERT(pRunInfo, "pParser can't be null");
    COREASSERT_ASSERT(pRunInfo, "pParser can't be null");

    if(g_pFlagHelp   ->Found()) show_help(pParser->GenerateHelpString());
    if(g_pFlagVersion->Found()) show_version();
}

acow_internal_function inline void
get_results_group_directories(Core::RunInfo *pRunInfo) noexcept
{
    COREASSERT_ASSERT(pRunInfo, "pRunInfo can't be null");

    //--------------------------------------------------------------------------
    // Images Dir.
    if(g_pFlagDirsImages->Found())
        pRunInfo->dirs_Images = g_pFlagDirsImages->GetValues();

    acow::algo::sort_and_unique(pRunInfo->dirs_Images);
    acow::algo::for_each(pRunInfo->dirs_Images, [](std::string &path){
        path = CoreFS::ExpandUserAndMakeAbs(path);
    });

    if(pRunInfo->dirs_Images.empty())
        pRunInfo->dirs_Images.push_back(CoreFS::CurrentDirectory());

    //--------------------------------------------------------------------------
    // Allowed Ext.
    if(g_pFlagDirAllowedExt->Found())
        pRunInfo->dirs_ImagesAllowedExtensions = g_pFlagDirAllowedExt->GetValues();

    acow::algo::sort_and_unique(pRunInfo->dirs_ImagesAllowedExtensions);
    if(pRunInfo->dirs_ImagesAllowedExtensions.empty())
        pRunInfo->dirs_ImagesAllowedExtensions.push_back("png"); // COWTODO(n2omatt): Remove magic values.

    //--------------------------------------------------------------------------
    // Output Dir.
    if(g_pFlagDirOutput->Found())
        pRunInfo->dir_Output = g_pFlagDirOutput->GetValue();

    if(pRunInfo->dir_Output.empty())
        pRunInfo->dir_Output = CoreFS::Join(CoreFS::CurrentDirectory(), {"output"}); // COWTODO(n2omatt): Remove magic values.
}

acow_internal_function inline void
get_results_group_image_info(Core::RunInfo *pRunInfo) noexcept
{
    COREASSERT_ASSERT(pRunInfo, "pRunInfo can't be null");

    //--------------------------------------------------------------------------
    // Image Name.
    if(g_pFlagSheetImageName->Found())
        pRunInfo->sheet_ImageName = g_pFlagSheetImageName->GetValue();

    if(pRunInfo->sheet_ImageName.empty())
        pRunInfo->sheet_ImageName = "sheet"; // COWTODO(n2omatt): Remove magic values.

    //--------------------------------------------------------------------------
    // Image Format.
    if(g_pFlagSheetImageFormat->Found())
        pRunInfo->sheet_ImageFormat = g_pFlagSheetImageFormat->GetValue();

    if(pRunInfo->sheet_ImageFormat.empty())
        pRunInfo->sheet_ImageFormat = "png"; // COWTODO(n2omatt): Remove magic values.

    //--------------------------------------------------------------------------
    // Debug Images.
    if(g_pFlagSheetImageDebug->Found())
        pRunInfo->sheet_ImageDebug = true;

    //--------------------------------------------------------------------------
    // Size Min
    if(g_pFlagSheetSizeMin->Found())
    {
        pRunInfo->sheet_SizeMin = parse_size_from_str(
            g_pFlagSheetSizeMin->GetValue()
        );
    }

    //--------------------------------------------------------------------------
    // Size Max.
    if(g_pFlagSheetSizeMax->Found())
    {
        pRunInfo->sheet_SizeMax = parse_size_from_str(
            g_pFlagSheetSizeMin->GetValue()
        );
    }

    //--------------------------------------------------------------------------
    // Force POT.
    if(g_pFlagSheetSizeForcePOT->Found())
        pRunInfo->sheet_ForcePOT = true;

    //--------------------------------------------------------------------------
    // Force Square
    if(g_pFlagSheetSizeForceSquare->Found())
        pRunInfo->sheet_ForceSquare = true;
}

acow_internal_function inline void
get_results_group_data_info(Core::RunInfo *pRunInfo) noexcept
{
    COREASSERT_ASSERT(pRunInfo, "pRunInfo can't be null");

    //--------------------------------------------------------------------------
    // Data Name.
    if(g_pFlagSheetDataName->Found())
        pRunInfo->sheet_DataName = g_pFlagSheetDataName->GetValue();

    if(pRunInfo->sheet_DataName.empty())
        pRunInfo->sheet_DataName = "sheet"; // COWTODO(n2omatt): Remove magic values.

    //--------------------------------------------------------------------------
    // Data Format.
    if(g_pFlagSheetDataFormat->Found())
        pRunInfo->sheet_DataFormat = g_pFlagSheetDataFormat->GetValue();

    if(pRunInfo->sheet_DataFormat.empty())
        pRunInfo->sheet_DataFormat = "cooper"; // COWTODO(n2omatt): Remove magic values.
}

acow_internal_function inline void
get_results_group_pack(Core::RunInfo *pRunInfo) noexcept
{
    COREASSERT_ASSERT(pRunInfo, "pRunInfo can't be null");

    //--------------------------------------------------------------------------
    // Sort Type.
    if(g_pFlagPackSortType->Found())
        pRunInfo->pack_SortType = g_pFlagPackSortType->GetValue();

    if(pRunInfo->pack_SortType.empty())
        pRunInfo->pack_SortType = "area"; // COWTODO(n2omatt): Remove magic values.
}

acow_internal_function inline void
get_results_group_gui(Core::RunInfo *pRunInfo) noexcept
{
    COREASSERT_ASSERT(pRunInfo, "pRunInfo can't be null");

    // GUI.
    if(g_pFlagGUI->Found())
        pRunInfo->gui_Enabled = true;
}


//----------------------------------------------------------------------------//
// Public Functions                                                           //
//----------------------------------------------------------------------------//
Core::RunInfo
Core::ParseCommandLine(int argc, char *argv[])
{
    //--------------------------------------------------------------------------
    // Init the flags.
    Parser parser(CMD::DieOnNonValidFlags);

    init_group_help       (&parser);
    init_group_directories(&parser);
    init_group_image_info (&parser);
    init_group_data_info  (&parser);
    init_group_pack       (&parser);
    init_group_gui        (&parser);

    parser.Parse(argc, argv);

    //--------------------------------------------------------------------------
    // Get the flags results.
    Core::RunInfo run_info = {};

    get_results_group_help       (&run_info, &parser);
    get_results_group_directories(&run_info);
    get_results_group_image_info (&run_info);
    get_results_group_data_info  (&run_info);
    get_results_group_pack       (&run_info);
    get_results_group_gui        (&run_info);


    return run_info;
}