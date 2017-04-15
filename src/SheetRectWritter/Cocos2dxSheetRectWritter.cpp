//Header
#include "include/SheetRectWritter/Cocos2dxSheetRectWritter.h"
//qtplist
#include "lib/qtplist/plistserializer.h"


////////////////////////////////////////////////////////////////////////////////
// Interface Methods                                                          //
////////////////////////////////////////////////////////////////////////////////
void Cocos2dxSheetRectWritter::write(const SheetWritterOptions &options) const
{
    //COWTODO(n2omatt): Make sure that images and rects are the same size.

    //Build the Frames.
    QVariantMap frames_map;
    for(int i = 0; i < options.images.size(); ++i)
    {
        auto image = options.images[i];
        auto rect  = options.rects [i];

        QVariantMap frame_map;

        //Frame
        frame_map["frame"] = QString().sprintf(
            "{{%d,%d}, {%d,%d}}",
            rect.x(),
            rect.y(),
            rect.width(),
            rect.height()
        );

        //Offset
        //COWTODO: Make the packer strip transparent stuff.

        //Rotate
        //COWTODO: Make the packer rotate the image to better results.
        frame_map["rotated"] = false;

        //SourceColorRect
        //COWTODO: ???

        //SourceSize
        frame_map["sourceSize"] = QString().sprintf(
            "{%d,%d}",
            rect.width(),
            rect.height()
        );

        frames_map[image.getFilename()] = frame_map;
    }


    //Build Metadata.
    QVariantMap metadata_map;
    metadata_map["format"             ] = 2; //COWTODO(n2omatt) Remove magic number.
    metadata_map["realTextureFileName"] = options.imageOutputFilename;
    metadata_map["textureFileName"    ] = options.imageOutputFilename;
    metadata_map["size"               ] = QString().sprintf(
        "{%d, %d}",
        options.sheetSize.width(),
        options.sheetSize.height()
    );

    //Build the Plist.
    QVariantMap plist_map;
    plist_map["frames"  ] = frames_map;
    plist_map["metadata"] = metadata_map;

    //Write to file.
    //COWTODO(n2omatt): Error checking...
    auto filename   = options.dataOutputFilename;
    auto outpath    = options.outputPath;
    auto final_path = QDir(outpath).filePath(filename);

    QFile file(final_path);
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << PListSerializer::toPList(plist_map);

        file.close();
    }
}
