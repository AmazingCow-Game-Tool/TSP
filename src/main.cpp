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




//         // 1. Show a simple window.
//         // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets
//         // automatically appears in a window called "Debug".
//         // {
//         //     static float f = 0.0f;
//         //     static int counter = 0;
//         //     ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
//         //     ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
//         //     ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

//         //     ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
//         //     ImGui::Checkbox("Another Window", &show_another_window);

//         //     if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
//         //         counter++;
//         //     ImGui::SameLine();
//         //     ImGui::Text("counter = %d", counter);

//         //     ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//         // }
//         ImGui::Begin("asdf");
//         if (ImGui::BeginMenuBar())
//         {
//             if (ImGui::BeginMenu("Menu"))
//             {
//                 ImGui::EndMenu();
//             }
//             if (ImGui::BeginMenu("Examples"))
//             {
//                 // ImGui::MenuItem("Main menu bar", NULL, &show_app_main_menu_bar);
//                 // ImGui::MenuItem("Console", NULL, &show_app_console);
//                 // ImGui::MenuItem("Log", NULL, &show_app_log);
//                 // ImGui::MenuItem("Simple layout", NULL, &show_app_layout);
//                 // ImGui::MenuItem("Property editor", NULL, &show_app_property_editor);
//                 // ImGui::MenuItem("Long text display", NULL, &show_app_long_text);
//                 // ImGui::MenuItem("Auto-resizing window", NULL, &show_app_auto_resize);
//                 // ImGui::MenuItem("Constrained-resizing window", NULL, &show_app_constrained_resize);
//                 // ImGui::MenuItem("Simple overlay", NULL, &show_app_fixed_overlay);
//                 // ImGui::MenuItem("Manipulating window titles", NULL, &show_app_window_titles);
//                 // ImGui::MenuItem("Custom rendering", NULL, &show_app_custom_rendering);
//                 ImGui::EndMenu();
//             }
//             if (ImGui::BeginMenu("Help"))
//             {
//                 // ImGui::MenuItem("Metrics", NULL, &show_app_metrics);
//                 // ImGui::MenuItem("Style Editor", NULL, &show_app_style_editor);
//                 // ImGui::MenuItem("About Dear ImGui", NULL, &show_app_about);
//                 ImGui::EndMenu();
//             }
//             ImGui::EndMenuBar();
//     }

//     ImGui::Spacing();
//     if (ImGui::CollapsingHeader("Help"))
//     {
//         ImGui::TextWrapped("This window is being created by the ShowDemoWindow() function. Please refer to the code in imgui_demo.cpp for reference.\n\n");
//         ImGui::Text("USER GUIDE:");
//     }

//     if (ImGui::CollapsingHeader("Window options"))
//     {
//         // ImGui::Checkbox("No titlebar", &no_titlebar); ImGui::SameLine(150);
//         // ImGui::Checkbox("No scrollbar", &no_scrollbar); ImGui::SameLine(300);
//         // ImGui::Checkbox("No menu", &no_menu);
//         // ImGui::Checkbox("No move", &no_move); ImGui::SameLine(150);
//         // ImGui::Checkbox("No resize", &no_resize); ImGui::SameLine(300);
//         // ImGui::Checkbox("No collapse", &no_collapse);
//         // ImGui::Checkbox("No close", &no_close); ImGui::SameLine(150);
//         // ImGui::Checkbox("No nav", &no_nav);

//         if (ImGui::TreeNode("Style"))
//         {
//             ImGui::TreePop();
//         }

//         if (ImGui::TreeNode("Capture/Logging"))
//         {
//             ImGui::TextWrapped("The logging API redirects all text output so you can easily capture the content of a window or a block. Tree nodes can be automatically expanded. You can also call ImGui::LogText() to output directly to the log without a visual output.");
//             ImGui::LogButtons();
//             ImGui::TreePop();
//         }
//     }
//     ImGui::End();


//     return 0;
// }


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
    char b[4] = {'p','a','c','k'};
    char c[] = {'p','a','c','k','2'};

    auto equal = acow_memcmp(b, c, 4);

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









// //     //--------------------------------------------------------------------------
// //     // Packer.
// //     auto packer_options = Packer::Options {
// //         .sheet_ImageFilename = "test",
// //         .sheet_DataFilename  = "test",
// //         .sheet_OutputPath    = "~/Desktop/TestSheet"
// //     };

// //     packer.SetImages          (images_list               );
// //     packer.SetPackingMethod   (p_packing_strategy  .get());
// //     packer.SetSheetImageWriter(p_sheet_image_writer.get());
// //     packer.SetSheetRectWriter (p_sheet_rect_writer .get());
// //     packer.SetSortMethod      (p_sort_method       .get());
// //     ;

// //     return EXIT_SUCCESS;
// // }
