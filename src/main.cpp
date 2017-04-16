//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        main.cpp                                  //
//            █ █        █ █        TSP                                       //
//             ████████████                                                   //
//           █              █       Copyright (c) 2017                        //
//          █     █    █     █      AmazingCow - www.AmazingCow.com           //
//          █     █    █     █                                                //
//           █              █       N2OMatt - n2omatt@amazingcow.com          //
//             ████████████         www.amazingcow.com/n2omatt                //
//                                                                            //
//                  This software is licensed as GPLv3                        //
//                 CHECK THE COPYING FILE TO MORE DETAILS                     //
//                                                                            //
//    Permission is granted to anyone to use this software for any purpose,   //
//   including commercial applications, and to alter it and redistribute it   //
//               freely, subject to the following restrictions:               //
//                                                                            //
//     0. You **CANNOT** change the type of the license.                      //
//     1. The origin of this software must not be misrepresented;             //
//        you must not claim that you wrote the original software.            //
//     2. If you use this software in a product, an acknowledgment in the     //
//        product IS HIGHLY APPRECIATED, both in source and binary forms.     //
//        (See opensource.AmazingCow.com/acknowledgment.html for details).    //
//        If you will not acknowledge, just send us a email. We'll be         //
//        *VERY* happy to see our work being used by other people. :)         //
//        The email is: acknowledgment_opensource@AmazingCow.com              //
//     3. Altered source versions must be plainly marked as such,             //
//        and must not be misrepresented as being the original software.      //
//     4. This notice may not be removed or altered from any source           //
//        distribution.                                                       //
//     5. Most important, you must have fun. ;)                               //
//                                                                            //
//      Visit opensource.amazingcow.com for more open-source projects.        //
//                                                                            //
//                                  Enjoy :)                                  //
//----------------------------------------------------------------------------//

//std
#include <iostream>
//CMD
#include "lib/CMD/include/CMD.h"
//TSP
#include "include/TSP.h"

////////////////////////////////////////////////////////////////////////////////
// Types                                                                      //
////////////////////////////////////////////////////////////////////////////////
struct RunInfo
{
    //Images
    std::string inputImagesPath;
    //Exporter
    std::string exporter;
    //Output
    std::string imgFilename;
    std::string dataFilename;
    std::string outputPath;
};


////////////////////////////////////////////////////////////////////////////////
// Function Declarations                                                      //
////////////////////////////////////////////////////////////////////////////////
void show_help(int exitCode)
{
    std::cout << "help" << std::endl;
    exit(exitCode);
}

void show_version()
{
    std::cout << "version" << std::endl;
    exit(0);
}

void show_error(const QString &msg)
{
    std::cerr << msg.toStdString() << std::endl;
    exit(1);
}

RunInfo parse_cmdline(int argc, char **argv)
{
    //Setup the Flags.
    //  Help / Version
    auto help_flag = CMD::Flag()
        .RequiresNoArgs()
        .StopOnView()
        .Short("h")
        .Long("help");

    auto version_flag = CMD::Flag()
        .RequiresNoArgs()
        .StopOnView()
        .Short("v")
        .Long("version");

    //  Input
    auto input_images_flag = CMD::Flag()
        .RequiresArgs()
        .Short("i")
        .Long("input-images-path");

    //  Exporter
    auto exporter_flag =  CMD::Flag()
        .RequiresArgs()
        .Short("e")
        .Long("exporter")
        .Default("cocos2d");

    //  Output
    auto image_filename_flag = CMD::Flag()
        .RequiresArgs()
        .Long("image-filename")
        .Default("spritesheet.png");

    auto data_filename_flag = CMD::Flag()
        .RequiresArgs()
        .Long("data-filename")
        .Default("spritesheet.plist");

    auto output_path_flag = CMD::Flag()
        .RequiresArgs()
        .Short("o")
        .Long("output")
        .Default(QDir().absolutePath().toStdString());


    //Setup the Parser.
    auto cmd_parser = CMD::Parser(argc, argv);
    cmd_parser
        .addFlag(&help_flag   )
        .addFlag(&version_flag)

        .addFlag(&input_images_flag)

        .addFlag(&exporter_flag)

        .addFlag(&image_filename_flag)
        .addFlag(&data_filename_flag )
        .addFlag(&output_path_flag   );

    cmd_parser.parse();


    //Check which flags are found.
    RunInfo run_info;

    //  Help / Version
    if(help_flag.wasFound())
        show_help(0);
    else if(version_flag.wasFound())
        show_version();

    //  Input
    if(!input_images_flag.wasFound())
    {
        auto msg = QString().sprintf(
            "[FATAL] Missing input images.\n\tUse (%s) to specify them",
            input_images_flag.getShortLongDisplayStr().c_str()
        );

        show_error(msg);
    }
    run_info.inputImagesPath = input_images_flag.getRequiredValues()[0];

    //  Exporter
    run_info.exporter = (exporter_flag.wasFound())
        ? exporter_flag.getRequiredValues()[0]
        : exporter_flag.getDefaultValue();

    // Output
    run_info.imgFilename = (image_filename_flag.wasFound())
        ? image_filename_flag.getRequiredValues()[0]
        : image_filename_flag.getDefaultValue();

    run_info.dataFilename = (data_filename_flag.wasFound())
        ? data_filename_flag.getRequiredValues()[0]
        : data_filename_flag.getDefaultValue();

    run_info.outputPath = (output_path_flag.wasFound())
        ? output_path_flag.getRequiredValues()[0]
        : output_path_flag.getDefaultValue();

    return run_info;
}

void run(const RunInfo &runInfo)
{
    //Setup ImageFinder.
    auto image_finder_options = ImageFinder::Options {
        .startPath = QString::fromStdString(runInfo.inputImagesPath)
    };
    image_finder_options.allowedFiletypes.push_back("*.png"); //COWTODO(n2omatt): Remove magic value.

    auto image_finder = ImageFinder(image_finder_options);
    auto image_paths  = image_finder.findImagesPaths();


    //Setup ImageLoader.
    auto image_loader = ImageLoader(image_paths);
    auto image_list   = image_loader.loadImages();


    //Setup Packer.
    auto packer_options = Packer::Options {
        .imgFilename  = QString::fromStdString(runInfo.imgFilename ),
        .dataFilename = QString::fromStdString(runInfo.dataFilename),
        .outputPath   = QString::fromStdString(runInfo.outputPath  )
    };
    auto packer = Packer(packer_options);
    packer.setImages(image_list);

    packer.setSortMethod   (std::make_unique<WidthImageSorter>     ());
    packer.setPackingMethod(std::make_unique<SimplePackingStrategy>());

    packer.setSheetImageWritter(std::make_unique<BasicSheetImageWritter>  ());
    packer.setSheetRectWritter (std::make_unique<Cocos2dxSheetRectWritter>());

    packer.pack();
}



////////////////////////////////////////////////////////////////////////////////
// Entry point                                                                //
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    auto run_info = parse_cmdline(argc, argv);
    run(run_info);

    return 0;
}


////////////////////////////////////////////////////////////////////////////////
// Function Definitions                                                       //
////////////////////////////////////////////////////////////////////////////////

