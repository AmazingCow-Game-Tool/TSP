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
