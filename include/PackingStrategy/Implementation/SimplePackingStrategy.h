#pragma once

// std
#include <vector>
// AmazingCow Libs
#include "acow/cpp_goodies.h"
#include "acow/math_goodies.h"
// TSP
#include "include/PackingStrategy/Interface/IPackingStrategy.h"


class SimplePackingStrategy :
    public IPackingStrategy
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    ACOW_SMART_PTRS_OF(SimplePackingStrategy);


    //------------------------------------------------------------------------//
    // Inner Types                                                            //
    //------------------------------------------------------------------------//
private:
    struct Node
    {
        //----------------------------------------------------------------------
        // Typedefs
        ACOW_SHARED_PTR_OF(Node);

        //----------------------------------------------------------------------
        // iVars
        int                id;
        bool             used;
        acow::math::Rect rect;

        SPtr pDown;
        SPtr pRight;

        //----------------------------------------------------------------------
        // CTOR
        Node(int x, int y, int w, int h) :
            id    (-1   ),
            used  (false),
            rect  (x, y, w, h),
            pDown (nullptr),
            pRight(nullptr)
        {
            // Empty...
        }

        Node(int x, int y, const acow::math::Size &size) :
            Node(x, y, size.width, size.height)
        {
            // Empty...
        }
    }; // struct Node


    //------------------------------------------------------------------------//
    // Interface Methods                                                      //
    //------------------------------------------------------------------------//
public:
    void Pack(const std::vector<Image::SPtr> &images) noexcept override;

    const std::vector<acow::math::Rect>& GetOutputRects() const noexcept override;

    const acow::math::Size& GetSheetSize() const noexcept override;


    //------------------------------------------------------------------------//
    // Private Methods                                                        //
    //------------------------------------------------------------------------//
private:
    Node::SPtr FindNode (Node::SPtr pNode, const acow::math::Size &size);
    Node::SPtr SplitNode(Node::SPtr pNode, const acow::math::Size &size);

    Node::SPtr GrowNode      (const acow::math::Size &size);
    Node::SPtr GrowNode_Right(const acow::math::Size &size);
    Node::SPtr GrowNode_Down (const acow::math::Size &size);


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    Node::SPtr                    m_pRootNode;
    acow::math::Size              m_sheetSize;
    std::vector<acow::math::Rect> m_outputRects;
};
