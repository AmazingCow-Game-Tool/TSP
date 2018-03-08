cmake_minimum_required(VERSION 3.5)

##----------------------------------------------------------------------------##
## Project                                                                    ##
##----------------------------------------------------------------------------##
##------------------------------------------------------------------------------
## Settings
project(tsp)
##------------------------------------------------------------------------------
## Include paths.
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)


##----------------------------------------------------------------------------##
## Libraries                                                                  ##
##----------------------------------------------------------------------------##
##------------------------------------------------------------------------------
## Defines
add_definitions(-DACOW_MATH_HAS_SDL_SUPPORT=1)

##------------------------------------------------------------------------------
## AmazingCow Libs
add_subdirectory(lib/acow_math_goodies)
add_subdirectory(lib/acow_cpp_goodies )
add_subdirectory(lib/acow_algo        )
add_subdirectory(lib/acow_sdl_goodies )
add_subdirectory(lib/acow_nt_posix    )
add_subdirectory(lib/CoreAssert       )
add_subdirectory(lib/CoreDir          )
add_subdirectory(lib/CoreFile         )
add_subdirectory(lib/CoreFS           )
add_subdirectory(lib/CoreINI          )
add_subdirectory(lib/CoreLog          )
add_subdirectory(lib/CoreString       )
add_subdirectory(lib/libtermcolor     )
add_subdirectory(lib/CMD              )


##----------------------------------------------------------------------------##
## Source Files                                                               ##
##----------------------------------------------------------------------------##
set(SOURCE_FILES
    ./src/main.cpp
    ## CORE
    ./src/Core/RunInfo.cpp
    ./src/Core/Image/Image.cpp
    ./src/Core/ImageFinder/DirectoryImageFinder.cpp
    ./src/Core/ImageLoader/ImageLoader.cpp
    ./src/Core/PackingStrategy/SimplePackingStrategy.cpp
    ./src/Core/SheetImageWriter/BasicSheetImageWriter.cpp
    ./src/Core/SheetRectWriter/CooperSheetRectWriter.cpp
    ./src/Core/private/Logger.cpp
    ./src/Core/ImageSorter/Factory/ImageSorterFactory.cpp
    ## UI
    ./src/UI/UI.cpp
    ./src/UI/private/Logger.cpp
)

##----------------------------------------------------------------------------##
## Executable                                                                 ##
##----------------------------------------------------------------------------##
## Executable.
add_executable(tsp ${SOURCE_FILES})

## Dependecies.
target_link_libraries(tsp LINK_PUBLIC acow_math_goodies  )
target_link_libraries(tsp LINK_PUBLIC acow_cpp_goodies   )
target_link_libraries(tsp LINK_PUBLIC acow_algo          )
target_link_libraries(tsp LINK_PUBLIC acow_sdl_goodies   )
target_link_libraries(tsp LINK_PUBLIC CoreAssert         )
target_link_libraries(tsp LINK_PUBLIC CoreDir            )
target_link_libraries(tsp LINK_PUBLIC CoreIni            )
target_link_libraries(tsp LINK_PUBLIC CMD                )
target_link_libraries(tsp LINK_PUBLIC ${Qt5Gui_LIBRARIES})
