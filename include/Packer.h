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

public:
    Packer();

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
    QVector<Image> m_images;

    std::unique_ptr<IImageSorter>     m_pImageSorter;
    std::unique_ptr<IPackingStrategy> m_pPackingStrategy;

    std::unique_ptr<ISheetImageWritter> m_pSheetImageWritter;
    std::unique_ptr<ISheetRectWritter>  m_pSheetRectWritter;
};
