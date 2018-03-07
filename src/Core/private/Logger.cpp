// Header
#include "include/Core/private/Logger.h"
// AmazingCow Libs
#include "acow/cpp_goodies.h"
// Usings
using namespace TSP;


//----------------------------------------------------------------------------//
// Functions                                                                  //
//----------------------------------------------------------------------------//
CoreLog::Logger*
Core::Logger() noexcept
{
    acow_local_persist std::unique_ptr<CoreLog::Logger> s_pLogger(nullptr);
    if(!s_pLogger)
        s_pLogger = acow::make_unique<CoreLog::Logger>();

    return s_pLogger.get();
}