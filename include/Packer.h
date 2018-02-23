#pragma once

// std
#include <memory>
// TSP
#include "include/ImageSorter/ImageSorters.h"
#include "include/PackingStrategy/PackingStrategies.h"
#include "include/SheetImageWriter/SheetImageWriters.h"
#include "include/SheetRectWriter/SheetRectWriters.h"


class Packer
{
    //------------------------------------------------------------------------//
    // Inner Types                                                            //
    //------------------------------------------------------------------------//
public:
    struct Options
    {
        std::string imgFilename;
        std::string dataFilename;
        std::string outputPath;
    };

    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    Packer(const Options &options);

    //
public:
    void setImages(const std::vector<Image> &images);

    //
public:
    void setSortMethod   (std::unique_ptr<IImageSorter>     pImageSorter    );
    void setPackingMethod(std::unique_ptr<IPackingStrategy> pPackingStrategy);

    void setSheetImageWritter(std::unique_ptr<ISheetImageWriter> pSheetImageWritter);
    void setSheetRectWritter (std::unique_ptr<ISheetRectWriter>  pSheetRectWritter );

    //
public:
    void pack();


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    Options m_options;

    std::vector<Image> m_images;

    std::unique_ptr<IImageSorter>     m_pImageSorter;
    std::unique_ptr<IPackingStrategy> m_pPackingStrategy;

    std::unique_ptr<ISheetImageWriter> m_pSheetImageWriter;
    std::unique_ptr<ISheetRectWriter>  m_pSheetRectWriter;
}; // class Packer
