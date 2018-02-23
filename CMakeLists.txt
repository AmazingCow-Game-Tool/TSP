cmake_minimum_required(VERSION 3.5)
project(tsp)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(lib/acow_math_goodies)
add_subdirectory(lib/acow_cpp_goodies)
add_subdirectory(lib/CoreAssert)
add_subdirectory(lib/CoreFS)
add_subdirectory(lib/CoreDir)

include_directories(
    lib/stb_image
)


set(SOURCE_FILES
    ./src/main.cpp

    ./src/Image/Image.cpp
    ./src/ImageFinder/DirectoryImageFinder.cpp
    ./src/ImageLoader/ImageLoader.cpp


    ./src/PackingStrategy/SimplePackingStrategy.cpp

    ./src/SheetImageWriter/BasicSheetImageWriter.cpp

    ./src/Packer.cpp

    lib/stb_image/stb_image.h src/SheetRectWriter/CooperSheetRectWriter.cpp)

add_executable(tsp ${SOURCE_FILES})

target_link_libraries(tsp LINK_PUBLIC acow_math_goodies)
target_link_libraries(tsp LINK_PUBLIC acow_cpp_goodies)
target_link_libraries(tsp LINK_PUBLIC CoreAssert)
target_link_libraries(tsp LINK_PUBLIC CoreDir)

