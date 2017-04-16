//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Cocos2dxSheetRectWritter.cpp              //
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

//Header
#include "include/SheetRectWritter/Cocos2dxSheetRectWritter.h"
//qtplist
#include "lib/qtplist/plistserializer.h"


////////////////////////////////////////////////////////////////////////////////
// Interface Methods                                                          //
////////////////////////////////////////////////////////////////////////////////
void Cocos2dxSheetRectWritter::write(const SheetWritterOptions &options) const
{
    //COWTODO(n2omatt): Make sure that images and rects are the same size.

    //Build the Frames.
    QVariantMap frames_map;
    for(int i = 0; i < options.images.size(); ++i)
    {
        auto image = options.images[i];
        auto rect  = options.rects [i];

        QVariantMap frame_map;

        //Frame
        frame_map["frame"] = QString().sprintf(
            "{{%d,%d}, {%d,%d}}",
            rect.x(),
            rect.y(),
            rect.width(),
            rect.height()
        );

        //Offset
        //COWTODO: Make the packer strip transparent stuff.

        //Rotate
        //COWTODO: Make the packer rotate the image to better results.
        frame_map["rotated"] = false;

        //SourceColorRect
        //COWTODO: ???

        //SourceSize
        frame_map["sourceSize"] = QString().sprintf(
            "{%d,%d}",
            rect.width(),
            rect.height()
        );

        frames_map[image.getFilename()] = frame_map;
    }


    //Build Metadata.
    QVariantMap metadata_map;
    metadata_map["format"             ] = 2; //COWTODO(n2omatt) Remove magic number.
    metadata_map["realTextureFileName"] = options.imageOutputFilename;
    metadata_map["textureFileName"    ] = options.imageOutputFilename;
    metadata_map["size"               ] = QString().sprintf(
        "{%d, %d}",
        options.sheetSize.width(),
        options.sheetSize.height()
    );

    //Build the Plist.
    QVariantMap plist_map;
    plist_map["frames"  ] = frames_map;
    plist_map["metadata"] = metadata_map;

    //Write to file.
    //COWTODO(n2omatt): Error checking...
    auto filename   = options.dataOutputFilename;
    auto outpath    = options.outputPath;
    auto final_path = QDir(outpath).filePath(filename);

    QFile file(final_path);
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << PListSerializer::toPList(plist_map);

        file.close();
    }
}
