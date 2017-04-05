//Header
#include "include/PackingStrategy/SimplePackingStrategy.h"

////////////////////////////////////////////////////////////////////////////////
// Interface Methods                                                          //
////////////////////////////////////////////////////////////////////////////////
void SimplePackingStrategy::pack(const QVector<Image> &images)
{
    auto bigger_image = images[0];
    m_outputRects.reserve(images.size());

    //Start packing...
    m_pRootNode = std::make_shared<Node>(0, 0, bigger_image.getSize());

    for(int i = 0; i < images.size(); ++i)
    {
        const auto &image = images[i];

        auto image_size = image.getSize();
        auto p_node     = this->findNode(m_pRootNode, image_size);

        if(!p_node)
            p_node = this->growNode(image_size);
        else
            this->splitNode(p_node, image_size);

        p_node->id = i;

        auto rect = QRect(
            p_node->rect.x   (),
            p_node->rect.y   (),
            image_size.width (),
            image_size.height()
        );

        m_outputRects.push_back(rect);
    }//for


    //Find the Sheet Size.
    int max_w = 0;
    int max_h = 0;
    foreach(const QRect &rect, m_outputRects)
    {
        auto w = rect.x() + rect.width ();
        auto h = rect.y() + rect.height();

        if(w > max_w) max_w = w;
        if(h > max_h) max_h = h;
    }

    m_sheetSize.setWidth (max_w);
    m_sheetSize.setHeight(max_h);
}

const QVector<QRect>& SimplePackingStrategy::getOutputRects() const
{
    return m_outputRects;
}

const QSize& SimplePackingStrategy::getSheetSize() const
{
    return m_sheetSize;
}


////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
SimplePackingStrategy::Node::SPtr SimplePackingStrategy::findNode(
    Node::SPtr  pNode,
    const QSize &size)
{
    if(pNode->used)
    {
        auto p_found_node = this->findNode(pNode->pRight, size);

        if(p_found_node)
            return p_found_node;

        return this->findNode(pNode->pDown, size);
    }
    else if((size.width () <= pNode->rect.width ()) &&
            (size.height() <= pNode->rect.height()))
    {
        return pNode;
    }

    return nullptr;
}

SimplePackingStrategy::Node::SPtr SimplePackingStrategy::splitNode(
    Node::SPtr  pNode,
    const QSize &size)
{
    pNode->used = true;

    //Down Node.
    pNode->pDown = std::make_shared<Node>(
        pNode->rect.x(),
        pNode->rect.y() + size.height(),
        pNode->rect.width (),
        pNode->rect.height() - size.height()
    );

    //Right Node.
    pNode->pRight = std::make_shared<Node>(
        pNode->rect.x() + size.width(),
        pNode->rect.y(),
        pNode->rect.width () - size.width(),
        size.height()
    );

    return pNode;
}


SimplePackingStrategy::Node::SPtr SimplePackingStrategy::growNode(
    const QSize &size)
{
    //Just to reduce verbosity.
    auto root_w = m_pRootNode->rect.width ();
    auto root_h = m_pRootNode->rect.height();

    auto can_grow_down  = (size.width () <= root_w);
    auto can_grow_right = (size.height() <= root_h);

    //Attempt to keep square-ish by growing right
    //when height is much greater than width
    auto should_grow_right = can_grow_right &&
                             (root_h >= (root_w + size.width()));

    //Attempt to keep square-ish by growing down
    //when width is much greater than height
    auto should_grow_down = can_grow_down &&
                            (root_w >= (root_h + size.height()));

    if     (should_grow_right) return this->growNode_Right(size);
    else if(should_grow_down ) return this->growNode_Down (size);
    else if(can_grow_right   ) return this->growNode_Right(size);
    else if(can_grow_down    ) return this->growNode_Down (size);
    else                       return nullptr;
}

SimplePackingStrategy::Node::SPtr SimplePackingStrategy::growNode_Right(
    const QSize &size)
{
    auto p_new_root = std::make_shared<Node>(
        0, 0,
        m_pRootNode->rect.width() + size.width(),
        m_pRootNode->rect.height()
    );

    p_new_root->used   = true;
    p_new_root->pDown  = m_pRootNode;
    p_new_root->pRight = std::make_shared<Node>(
        m_pRootNode->rect.size().width(),
        0,
        size.width(),
        m_pRootNode->rect.height()
    );

    m_pRootNode = p_new_root;

    auto p_node = this->findNode(m_pRootNode, size);
    if(p_node)
        return this->splitNode(p_node, size);

    return nullptr;
}

SimplePackingStrategy::Node::SPtr SimplePackingStrategy::growNode_Down(
    const QSize &size)
{
    auto p_new_root = std::make_shared<Node>(
        0, 0,
        m_pRootNode->rect.width(),
        m_pRootNode->rect.height() + size.height()
    );

    p_new_root->used   = true;
    p_new_root->pRight = m_pRootNode;
    p_new_root->pDown  = std::make_shared<Node>(
        0,
        m_pRootNode->rect.height(),
        m_pRootNode->rect.width (),
        size.height()
    );

    m_pRootNode = p_new_root;

    auto p_node = this->findNode(m_pRootNode, size);
    if(p_node)
        return this->splitNode(p_node, size);

    return nullptr;
}
