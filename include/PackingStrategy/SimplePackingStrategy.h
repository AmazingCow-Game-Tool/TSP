//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        SimplePackingStrategy.h                   //
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
#include "include/PackingStrategy/IPackingStrategy.h"


class SimplePackingStrategy :
    public IPackingStrategy
{
    // Inner Types //
private:
    struct Node
    {
        // Typedefs //
        typedef std::shared_ptr<Node> SPtr;

        // iVars //
        int     id;
        bool  used;
        QRect rect;

        SPtr pDown;
        SPtr pRight;

        // CTOR //
        Node(int x, int y, int w, int h) :
            id    (-1   ),
            used  (false),
            rect  (x, y, w, h),
            pDown (nullptr),
            pRight(nullptr)
        {
            //Empty...
        }

        Node(int x, int y, const QSize &size) :
            Node(x, y, size.width(), size.height())
        {
            //Empty...
        }
    };

    // Interface Methods //
public:
    virtual void pack(const QVector<Image> &images) override;

    virtual const QVector<QRect>& getOutputRects() const override;

    virtual const QSize& getSheetSize() const override;


    // Private Methods //
private:
    Node::SPtr findNode (Node::SPtr pNode, const QSize &size);
    Node::SPtr splitNode(Node::SPtr pNode, const QSize &size);

    Node::SPtr growNode      (const QSize &size);
    Node::SPtr growNode_Right(const QSize &size);
    Node::SPtr growNode_Down (const QSize &size);


    // iVars //
private:
    Node::SPtr     m_pRootNode;
    QSize          m_sheetSize;
    QVector<QRect> m_outputRects;
};
