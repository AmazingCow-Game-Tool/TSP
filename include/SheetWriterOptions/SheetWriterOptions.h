#pragma once

// std
#include <string>
#include <vector>
// AmazingCow Libs
#include "acow/math_goodies.h"
// TSP
#include "include/Image/Images.h"


struct SheetWriterOptions
{
    std::string imageOutputFilename;
    std::string dataOutputFilename;

    std::string outputPath;

    std::vector<Image::SPtr>      images;
    std::vector<acow::math::Rect> rects;

    acow::math::Size sheetSize;
};
