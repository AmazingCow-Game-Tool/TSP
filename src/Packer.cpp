//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Packer.cpp                                //
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
#include "include/Packer.h"
//std
#include <algorithm> //for sort
//TSP
#include "include/SheetWritterOptions/SheetWritterOptions.h"

//
Packer::Packer(const Options &options) :
    m_options(options)
{

}

//
void Packer::setImages(const QVector<Image> &images)
{
    m_images = images;
}

//
void Packer::setSortMethod(std::unique_ptr<IImageSorter> pImageSorter)
{
    m_pImageSorter = std::move(pImageSorter);
}

void Packer::setPackingMethod(std::unique_ptr<IPackingStrategy> pPackingStrategy)
{
    m_pPackingStrategy = std::move(pPackingStrategy);
}

void Packer::setSheetImageWritter(
    std::unique_ptr<ISheetImageWritter> pSheetImageWritter)
{
    m_pSheetImageWritter = std::move(pSheetImageWritter);
}

void Packer::setSheetRectWritter(
    std::unique_ptr<ISheetRectWritter> pSheetRectWritter)
{
    m_pSheetRectWritter = std::move(pSheetRectWritter);
}


//
void Packer::pack()
{
    //Sort the images.
    std::sort(
        m_images.begin(),
        m_images.end  (),
        [this](const Image &i1, const Image &i2) {
            return m_pImageSorter->sort(i1, i2) > 0;
        }
    );

    //Pack
    m_pPackingStrategy->pack(m_images);


    //Setup the Writter Options
    auto writter_options = SheetWritterOptions {
        .imageOutputFilename = m_options.imgFilename,
        .dataOutputFilename  = m_options.dataFilename,
        .outputPath          = m_options.outputPath,

        .images    = m_images,
        .rects     = m_pPackingStrategy->getOutputRects(),
        .sheetSize = m_pPackingStrategy->getSheetSize()
    };

    //Write...
    m_pSheetImageWritter->write(writter_options);
    m_pSheetRectWritter->write (writter_options);
}
