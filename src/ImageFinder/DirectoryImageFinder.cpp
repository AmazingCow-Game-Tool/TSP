// Header
#include "include/Core/ImageFinder/Implementation/DirectoryImageFinder.h"
// AmazingCow Libs
#include "CoreFS/CoreFS.h"
#include "CoreDir/CoreDir.h"

// Usings
using namespace TSP;
using namespace Core;


//----------------------------------------------------------------------------//
// CTOR                                                                       //
//----------------------------------------------------------------------------//
DirectoryImageFinder::DirectoryImageFinder(const Options &options) noexcept
    : m_options(options)
{
    // Empty...
}


//----------------------------------------------------------------------------//
// Public Methods                                                             //
//----------------------------------------------------------------------------//
std::vector<std::string>
DirectoryImageFinder::FindImagesPaths() noexcept
{
    auto initial_path = CoreFS::AbsPath(
        CoreFS::ExpandUser(m_options.path_InitialPath)
    );

    auto file_paths = CoreDir::GetFiles(
        initial_path,
        ".*.png",
        true
    );

    return file_paths;
}
