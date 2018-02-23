// Header
#include "include/PackingStrategy/Implementation/SimplePackingStrategy.h"


//----------------------------------------------------------------------------//
// Interface Methods                                                          //
//----------------------------------------------------------------------------//
void SimplePackingStrategy::Pack(const std::vector<Image::SPtr> &images) noexcept
{
    auto p_bigger_image = images[0].get();
    m_outputRects.reserve(images.size());

    //--------------------------------------------------------------------------
    // Start packing...
    m_pRootNode = std::make_shared<Node>(0, 0, p_bigger_image->GetSize());

    for(int i = 0; i < images.size(); ++i)
    {
        const auto p_image = images[i].get();

        auto image_size = p_image->GetSize();
        auto p_node     = this->FindNode(m_pRootNode, image_size);

        if(!p_node)
            p_node = this->GrowNode(image_size);
        else
            this->SplitNode(p_node, image_size);

        p_node->id = i;

        auto rect = acow::math::Rect(
            p_node->rect.x   ,
            p_node->rect.y   ,
            image_size.width ,
            image_size.height
        );

        m_outputRects.push_back(rect);
    } // for

    //--------------------------------------------------------------------------
    // Find the Sheet Size.
    int max_w = 0;
    int max_h = 0;

    for(const auto &rect : m_outputRects)
    {
        auto w = rect.x + rect.GetWidth ();
        auto h = rect.y + rect.GetHeight();

        if(w > max_w) max_w = w;
        if(h > max_h) max_h = h;
    }

    m_sheetSize.SetWidth (max_w);
    m_sheetSize.SetHeight(max_h);
}

const std::vector<acow::math::Rect>&
    SimplePackingStrategy::GetOutputRects() const noexcept
{
    return m_outputRects;
}

const acow::math::Size& SimplePackingStrategy::GetSheetSize() const noexcept
{
    return m_sheetSize;
}


//----------------------------------------------------------------------------//
// Private Methods                                                            //
//----------------------------------------------------------------------------//
SimplePackingStrategy::Node::SPtr SimplePackingStrategy::FindNode(
    Node::SPtr              pNode,
    const acow::math::Size &size)
{
    if(pNode->used)
    {
        auto p_found_node = this->FindNode(pNode->pRight, size);

        if(p_found_node)
            return p_found_node;

        return this->FindNode(pNode->pDown, size);
    }
    else if((size.width  <= pNode->rect.GetWidth ()) &&
            (size.height <= pNode->rect.GetHeight()))
    {
        return pNode;
    }

    return nullptr;
}

SimplePackingStrategy::Node::SPtr SimplePackingStrategy::SplitNode(
    Node::SPtr              pNode,
    const acow::math::Size &size)
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


SimplePackingStrategy::Node::SPtr SimplePackingStrategy::GrowNode(
    const acow::math::Size &size)
{
    //--------------------------------------------------------------------------
    // Just to reduce verbosity.
    auto root_w = m_pRootNode->rect.GetWidth ();
    auto root_h = m_pRootNode->rect.GetHeight();

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

    if     (should_grow_right) return this->GrowNode_Right(size);
    else if(should_grow_down ) return this->GrowNode_Down (size);
    else if(can_grow_right   ) return this->GrowNode_Right(size);
    else if(can_grow_down    ) return this->GrowNode_Down (size);
    else                       return nullptr;
}

SimplePackingStrategy::Node::SPtr SimplePackingStrategy::GrowNode_Right(
    const acow::math::Size &size)
{
    auto p_new_root = std::make_shared<Node>(
        0, 0,
        m_pRootNode->rect.GetWidth () + size.width,
        m_pRootNode->rect.GetHeight()
    );

    p_new_root->used   = true;
    p_new_root->pDown  = m_pRootNode;
    p_new_root->pRight = std::make_shared<Node>(
        m_pRootNode->rect.GetWidth(),
        0,
        size.width,
        m_pRootNode->rect.GetHeight()
    );

    m_pRootNode = p_new_root;

    auto p_node = this->FindNode(m_pRootNode, size);
    if(p_node)
        return this->SplitNode(p_node, size);

    return nullptr;
}

SimplePackingStrategy::Node::SPtr SimplePackingStrategy::GrowNode_Down(
    const acow::math::Size &size)
{
    auto p_new_root = std::make_shared<Node>(
        0, 0,
        m_pRootNode->rect.GetWidth(),
        m_pRootNode->rect.GetHeight() + size.height
    );

    p_new_root->used   = true;
    p_new_root->pRight = m_pRootNode;
    p_new_root->pDown  = std::make_shared<Node>(
        0,
        m_pRootNode->rect.GetHeight(),
        m_pRootNode->rect.GetWidth (),
        size.height

    );

    m_pRootNode = p_new_root;

    auto p_node = this->FindNode(m_pRootNode, size);
    if(p_node)
        return this->SplitNode(p_node, size);

    return nullptr;
}
