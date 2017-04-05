#include <iostream>
#include "include/TSP.h"

using namespace std;

int main(int argc, char *argv[])
{
    QString output_path_image = "/home/n2omatt/Desktop/Image.png";
    QString output_path_rect  = "/home/n2omatt/Desktop/Image.plist";

    ImageFinder::Options options;
    options.startPath = "/home/n2omatt/Documents/Projects/AmazingCow/AmazingCow-Game/Game_Kaboom";
    options.allowedFiletypes.push_back("*.png");

    auto image_finder = ImageFinder(options);
    auto image_paths  = image_finder.findImagesPaths();

    auto image_loader = ImageLoader(image_paths);
    auto image_list   = image_loader.loadImages();

    auto packer = Packer();
    packer.setImages(image_list);

    packer.setSortMethod   (std::make_unique<WidthImageSorter>     ());
    packer.setPackingMethod(std::make_unique<SimplePackingStrategy>());

    packer.setSheetImageWritter(
        std::make_unique<BasicSheetImageWritter>(output_path_image)
    );
    packer.setSheetRectWritter(
        std::make_unique<Cocos2dxSheetRectWritter>(output_path_rect)
    );

    packer.pack();

    return 0;
}
