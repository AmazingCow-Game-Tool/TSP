#pragma once

// std
#include <memory>
// TSP
#include "include/Core/ImageSorter/ImageSorters.h"
#include "include/Core/PackingStrategy/PackingStrategies.h"
#include "include/Core/SheetImageWriter/SheetImageWriters.h"
#include "include/Core/SheetRectWriter/SheetRectWriters.h"

namespace TSP { namespace Core {

class Packer
{
    //------------------------------------------------------------------------//
    // Inner Types                                                            //
    //------------------------------------------------------------------------//
public:
    struct Options
    {
        std::string sheet_ImageFilename;
        std::string sheet_DataFilename;

        std::string sheet_OutputPath;
    };


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    explicit Packer(const Options &options);


    //
public:
    void SetImages(const std::vector<Image::SPtr> &images);

    //
public:
    void SetSortMethod   (IImageSorter     *pImageSorter    );
    void SetPackingMethod(IPackingStrategy *pPackingStrategy);

    void SetSheetImageWriter(ISheetImageWriter *pSheetImageWriter);
    void SetSheetRectWriter (ISheetRectWriter  *pSheetRectWriter );

    //
public:
    void Pack();


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    Options m_options;

    std::vector<Image::SPtr> m_images;

    IImageSorter     *m_pImageSorter;
    IPackingStrategy *m_pPackingStrategy;

    ISheetImageWriter *m_pSheetImageWriter;
    ISheetRectWriter  *m_pSheetRectWriter;

}; // class Packer

} // namespace Core
} // namespace TSP
