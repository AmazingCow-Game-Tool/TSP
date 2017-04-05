//Header
#include "include/Packer.h"

#include <algorithm>


//
Packer::Packer()
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

    m_pPackingStrategy->pack(m_images);

    m_pSheetImageWritter->write(
        m_images,
        m_pPackingStrategy->getOutputRects(),
        m_pPackingStrategy->getSheetSize()
    );

    m_pSheetRectWritter->write(
        m_images,
        m_pPackingStrategy->getOutputRects(),
        m_pPackingStrategy->getSheetSize()
    );
}
