//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : SimplePackingStrategy.cpp                                     //
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
#include "include/Core/PackingStrategy/Implementation/SimplePackingStrategy.h"
// AmazingCow Libs
#include "acow/cpp_goodies.h"
#include "CoreAssert/CoreAssert.h"

// Usings
using namespace TSP;
using namespace Core;


//----------------------------------------------------------------------------//
// Internal Types                                                             //
//----------------------------------------------------------------------------//
struct Node
{
    //------------------------------------------------------------------------//
    // Typedefs                                                               //
    //------------------------------------------------------------------------//
    ACOW_SHARED_PTR_OF(Node);

    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
    int                id;
    bool             used;
    acow::math::Rect rect;

    SPtr pDown;
    SPtr pRight;

    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
    Node(int x, int y, int w, int h) :
        id    (        -1),
        used  (     false),
        rect  (x, y, w, h),
        pDown (   nullptr),
        pRight(   nullptr)
    {
        // Empty...
    }

    Node(int x, int y, const acow::math::Size &size) :
        Node(x, y, size.width, size.height)
    {
        // Empty...
    }

}; // struct Node


//----------------------------------------------------------------------------//
// Internal Variables                                                         //
//----------------------------------------------------------------------------//
acow_global_variable Node::SPtr g_pRootNode = nullptr;


//----------------------------------------------------------------------------//
// Helper Functions                                                           //
//----------------------------------------------------------------------------//
acow_internal_function Node::SPtr
node_find(Node::SPtr pNode, const acow::math::Size &size) noexcept
{
    if(pNode->used)
    {
        auto p_found_node = node_find(pNode->pRight, size);

        if(p_found_node)
            return p_found_node;

        return node_find(pNode->pDown, size);
    }
    else if((size.width  <= pNode->rect.GetWidth ()) &&
            (size.height <= pNode->rect.GetHeight()))
    {
        return pNode;
    }

    return nullptr;
}

acow_internal_function Node::SPtr
node_split(Node::SPtr pNode, const acow::math::Size &size) noexcept
{
    pNode->used = true;

    //--------------------------------------------------------------------------
    // Down Node.
    pNode->pDown = std::make_shared<Node>(
        pNode->rect.x,
        pNode->rect.y + size.height,
        pNode->rect.GetWidth (),
        pNode->rect.GetHeight() - size.height
    );

    //--------------------------------------------------------------------------
    // Right Node.
    pNode->pRight = std::make_shared<Node>(
        pNode->rect.x + size.width,
        pNode->rect.y,
        pNode->rect.GetWidth() - size.width,
        size.height
    );

    return pNode;
}


acow_internal_function Node::SPtr
node_grow_right(const acow::math::Size &size) noexcept
{
    COREASSERT_ASSERT(g_pRootNode, "g_pRootNode can't be null");

    auto p_new_root = std::make_shared<Node>(
        0, 0,
        g_pRootNode->rect.GetWidth () + size.width,
        g_pRootNode->rect.GetHeight()
    );

    p_new_root->used   = true;
    p_new_root->pDown  = g_pRootNode;
    p_new_root->pRight = std::make_shared<Node>(
        g_pRootNode->rect.GetWidth(),
        0,
        size.width,
        g_pRootNode->rect.GetHeight()
    );

    g_pRootNode = p_new_root;

    auto p_node = node_find(g_pRootNode, size);
    if(p_node)
        return node_find(p_node, size);

    return nullptr;
}

acow_internal_function Node::SPtr
node_grow_down(const acow::math::Size &size) noexcept
{
    COREASSERT_ASSERT(g_pRootNode, "g_pRootNode can't be null");

    auto p_new_root = std::make_shared<Node>(
        0, 0,
        g_pRootNode->rect.GetWidth(),
        g_pRootNode->rect.GetHeight() + size.height
    );

    p_new_root->used   = true;
    p_new_root->pRight = g_pRootNode;
    p_new_root->pDown  = std::make_shared<Node>(
        0,
        g_pRootNode->rect.GetHeight(),
        g_pRootNode->rect.GetWidth (),
        size.height
    );

    g_pRootNode = p_new_root;

    auto p_node = node_find(g_pRootNode, size);
    if(p_node)
        return node_split(p_node, size);

    return nullptr;
}

acow_internal_function Node::SPtr
node_grow(const acow::math::Size &size) noexcept
{
    COREASSERT_ASSERT(g_pRootNode, "g_pRootNode can't be null");

    //--------------------------------------------------------------------------
    // Just to reduce verbosity.
    auto root_w = g_pRootNode->rect.GetWidth ();
    auto root_h = g_pRootNode->rect.GetHeight();

    auto can_grow_down  = (size.width  <= root_w);
    auto can_grow_right = (size.height <= root_h);

    //--------------------------------------------------------------------------
    // Attempt to keep square-ish by growing right
    // when height is much greater than width
    auto should_grow_right = can_grow_right &&
                             (root_h >= (root_w + size.width));

    //--------------------------------------------------------------------------
    // Attempt to keep square-ish by growing down
    // when width is much greater than height
    auto should_grow_down = can_grow_down &&
                            (root_w >= (root_h + size.height));

    if     (should_grow_right) return node_grow_right(size);
    else if(should_grow_down ) return node_grow_down (size);
    else if(can_grow_right   ) return node_grow_right(size);
    else if(can_grow_down    ) return node_grow_down (size);
    else                       return nullptr;
}



//----------------------------------------------------------------------------//
// Interface Methods                                                          //
//----------------------------------------------------------------------------//
IPackingStrategy::PackResults
SimplePackingStrategy::Pack(const std::vector<Image::SPtr> &images) noexcept
{
    PackResults pack_results = {};

    auto p_bigger_image = images[0].get();
    pack_results.rects.reserve(images.size());

    //--------------------------------------------------------------------------
    // Start packing...
    g_pRootNode = std::make_shared<Node>(0, 0, p_bigger_image->GetSize());

    for(int i = 0; i < images.size(); ++i)
    {
        auto p_image = images[i];
        COREASSERT_ASSERT(p_image, "p_image can't be null - Index: (%d)", i);

        auto image_size = p_image->GetSize();
        auto p_node     = node_find(g_pRootNode, image_size);

        if(!p_node)
            p_node = node_grow(image_size);
        else
            node_split(p_node, image_size);

        p_node->id = i;

        auto rect = acow::math::Rect(
            p_node->rect.x,
            p_node->rect.y,
            image_size.width,
            image_size.height
        );

        pack_results.rects.push_back(rect);
    } // for

    //--------------------------------------------------------------------------
    // Find the Sheet Size.
    int max_w = 0;
    int max_h = 0;

    for(const auto &rect : pack_results.rects)
    {
        auto w = rect.x + rect.GetWidth ();
        auto h = rect.y + rect.GetHeight();

        if(w > max_w) max_w = w;
        if(h > max_h) max_h = h;
    }

    pack_results.sheet_Size.SetWidth (max_w);
    pack_results.sheet_Size.SetHeight(max_h);

    return pack_results;
}
