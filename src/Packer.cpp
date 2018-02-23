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
void Packer::SetImages(const std::vector<Image::SPtr> &images)
{
    m_images = images;
}

//
void Packer::SetSortMethod(IImageSorter *pImageSorter)
{
    COREASSERT_ASSERT(pImageSorter, "pImageSorter can't be null");
    m_pImageSorter = pImageSorter;
}

void Packer::SetPackingMethod(IPackingStrategy *pPackingStrategy)
{
    COREASSERT_ASSERT(pPackingStrategy, "pPackingStrategy can't be null");
    m_pPackingStrategy = pPackingStrategy;
}

void Packer::SetSheetImageWriter(ISheetImageWriter *pSheetImageWriter)
{
    COREASSERT_ASSERT(pSheetImageWriter, "pSheetImageWriter can't be null");
    m_pSheetImageWriter = pSheetImageWriter;
}

void Packer::SetSheetRectWriter(ISheetRectWriter *pSheetRectWriter)
{
    COREASSERT_ASSERT(pSheetRectWriter, "pSheetRectWriter can't be null");
    m_pSheetRectWriter = pSheetRectWriter;
}


//
void Packer::Pack()
{
    //--------------------------------------------------------------------------
    // Sort the images.
    std::sort(
        m_images.begin(),
        m_images.end  (),
        [this](const Image::SPtr &i1, const Image::SPtr &i2) {
            return m_pImageSorter->Sort(i1, i2) > 0;
        }
    );

    //--------------------------------------------------------------------------
    // Pack.
    m_pPackingStrategy->Pack(m_images);

    //--------------------------------------------------------------------------
    // Setup the Writer Options.
    auto writer_options = SheetWriterOptions {
        .imageOutputFilename = m_options.sheet_ImageFilename,
        .dataOutputFilename  = m_options.sheet_DataFilename,
        .outputPath          = m_options.sheet_OutputPath,

        .images    = m_images,
        .rects     = m_pPackingStrategy->GetOutputRects(),
        .sheetSize = m_pPackingStrategy->GetSheetSize()
    };

    //--------------------------------------------------------------------------
    // Write.
    m_pSheetImageWriter->Write(writer_options);
    m_pSheetRectWriter ->Write(writer_options);
}
