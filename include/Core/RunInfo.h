#pragma once

// std
#include <string>
#include <vector>

namespace TSP { namespace Core {

struct RunInfo
{
    std::vector<std::string> dirs_Images;
    std::string              dir_Output;

    std::string sheet_ImageName;
    std::string sheet_DataName;

    std::string sheet_ImageFormat;
    std::string sheet_DataFormat;

    bool debug_Image;

    bool gui_Enabled;

}; // struct RunInfo

}  // namespace Core
}  // namespace TSP
