// Header
#include "include/Core/ImageFinder/Implementation/DirectoryImageFinder.h"
// AmazingCow Libs
#include "CoreAssert/CoreAssert.h"
#include "CoreFS/CoreFS.h"
#include "CoreDir/CoreDir.h"
// TSP
#include "include/Core/private/Logger.h"

// Usings
using namespace TSP;
using namespace Core;


//----------------------------------------------------------------------------//
// CTOR                                                                       //
//----------------------------------------------------------------------------//
DirectoryImageFinder::DirectoryImageFinder(
    const std::vector<std::string> &initialPaths,
    const std::vector<std::string> &allowedExtentions)
    // Members
    : m_initialPaths     (     initialPaths)
    , m_allowedExtensions(allowedExtentions)
{
    //--------------------------------------------------------------------------
    // Sanity checks.
    COREASSERT_THROW_IF(
        initialPaths.empty(),
        std::invalid_argument,
        "initialPaths can't be empty."
    );

    COREASSERT_THROW_IF(
        allowedExtentions.empty(),
        std::invalid_argument,
        "allowedExtentions can't be empty."
    );
}


//----------------------------------------------------------------------------//
// Public Methods                                                             //
//----------------------------------------------------------------------------//
std::vector<std::string>
DirectoryImageFinder::FindImagesPaths()
{
    auto file_paths = std::vector<std::string>();
    auto p_logger = Core::Logger();
    for(int i = 0; i < m_initialPaths.size(); ++i)
    {
        auto initial_path = m_initialPaths[i];

        //----------------------------------------------------------------------
        // Check if path is empty...
        COREASSERT_THROW_IF(
            initial_path.empty(),
            std::logic_error,
            "Path can't be empty - Index: (%d)",
            i
        );

        //----------------------------------------------------------------------
        // Check if path is a valid directory.
        initial_path = CoreFS::ExpandUserAndMakeAbs(initial_path);
        COREASSERT_THROW_IF(
            !CoreFS::IsDir(initial_path),
            std::logic_error,
            "Path doesn't no refer to a directory - Index: (%d) - Path: (%s)",
            i,
            initial_path.c_str()
        );

        p_logger->Debug(
            "Finding images paths (%d/%d) - Initial Path: (%s)",
            i+1,
            m_initialPaths.size(),
            initial_path
        );

        //----------------------------------------------------------------------
        // Get the images.
        auto curr_file_paths = CoreDir::GetFiles(
            initial_path,
            ".*.png", //COWTODO(n2omatt): Make the allowedExtensions count...
            true
        );


        //----------------------------------------------------------------------
        // Log.
        p_logger->Debug("Found: (%d) images.", curr_file_paths.size());
        for(const auto &path : curr_file_paths)
            p_logger->Debug("   -- Path: (%s)", path);

        //----------------------------------------------------------------------
        // Merge the current results to the grand total.
        if(curr_file_paths.empty())
            continue;

        file_paths.reserve(file_paths.size() + curr_file_paths.size());
        std::copy(
            std::begin        (curr_file_paths),
            std::end          (curr_file_paths),
            std::back_inserter(file_paths     )
        );
    }

    p_logger->Debug("Found (%d) images total", file_paths.size());

    return file_paths;
}
