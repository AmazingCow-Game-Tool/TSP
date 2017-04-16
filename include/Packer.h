//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Packer.h                                  //
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

#pragma once

//std
#include <memory>
//QT
#include <QtCore>
//TSP
#include "include/ImageSorter/IImageSorter.h"
#include "include/PackingStrategy/IPackingStrategy.h"
#include "include/SheetImageWritter/ISheetImageWritter.h"
#include "include/SheetRectWritter/ISheetRectWritter.h"

class Packer
{
    // Inner Types //
public:
    struct Options
    {
        QString imgFilename;
        QString dataFilename;
        QString outputPath;
    };

    // CTOR / DTOR //
public:
    Packer(const Options &options);

    //
public:
    void setImages(const QVector<Image> &images);

    //
public:
    void setSortMethod   (std::unique_ptr<IImageSorter>     pImageSorter    );
    void setPackingMethod(std::unique_ptr<IPackingStrategy> pPackingStrategy);

    void setSheetImageWritter(std::unique_ptr<ISheetImageWritter> pSheetImageWritter);
    void setSheetRectWritter (std::unique_ptr<ISheetRectWritter>  pSheetRectWritter );

    //
public:
    void pack();


    // iVars //
private:
    Options m_options;

    QVector<Image> m_images;

    std::unique_ptr<IImageSorter>     m_pImageSorter;
    std::unique_ptr<IPackingStrategy> m_pPackingStrategy;

    std::unique_ptr<ISheetImageWritter> m_pSheetImageWritter;
    std::unique_ptr<ISheetRectWritter>  m_pSheetRectWritter;
};
