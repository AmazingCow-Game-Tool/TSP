// Header
#include "include/Packer.h"
// std
#include <algorithm> // for sort
// TSP
#include "include/SheetWriterOptions/SheetWriterOptions.h"

//
Packer::Packer(const Options &options) :
    m_options(options)
{

}

//
void Packer::setImages(const std::vector<Image> &images)
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
//
//void Packer::setSheetImageWriter(
//    std::unique_ptr<ISheetImageWriter> pSheetImageWriter)
//{
//    m_pSheetImageWriter = std::move(pSheetImageWriter);
//}
//
//void Packer::setSheetRectWriter(
//    std::unique_ptr<ISheetRectWriter> pSheetRectWriter)
//{
//    m_pSheetRectWriter = std::move(pSheetRectWriter);
//}


//
void Packer::pack()
{
    //--------------------------------------------------------------------------
    // Sort the images.
    std::sort(
        m_images.begin(),
        m_images.end  (),
        [this](const Image &i1, const Image &i2) {
            return m_pImageSorter->Sort(i1, i2) > 0;
        }
    );

    //--------------------------------------------------------------------------
    // Pack
    m_pPackingStrategy->Pack(m_images);

    //--------------------------------------------------------------------------
    // Setup the Writer Options
    auto writer_options = SheetWriterOptions {
        .imageOutputFilename = m_options.imgFilename,
        .dataOutputFilename  = m_options.dataFilename,
        .outputPath          = m_options.outputPath,

        .images    = m_images,
        .rects     = m_pPackingStrategy->GetOutputRects(),
        .sheetSize = m_pPackingStrategy->GetSheetSize()
    };

    //--------------------------------------------------------------------------
    // Write...
    m_pSheetImageWriter->Write(writer_options);
    m_pSheetRectWriter ->Write(writer_options);
}
