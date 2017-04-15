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
