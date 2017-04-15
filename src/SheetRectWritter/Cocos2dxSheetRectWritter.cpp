//Header
#include "include/SheetRectWritter/Cocos2dxSheetRectWritter.h"
//qtplist
#include "lib/qtplist/plistserializer.h"


////////////////////////////////////////////////////////////////////////////////
// CTOR                                                                       //
////////////////////////////////////////////////////////////////////////////////
Cocos2dxSheetRectWritter::Cocos2dxSheetRectWritter(const QString &outputPath) :
    m_outputPath(outputPath)
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Interface Methods                                                          //
////////////////////////////////////////////////////////////////////////////////
void Cocos2dxSheetRectWritter::write(
    const QVector<Image> &images,
    const QVector<QRect> &rects,
    const QSize          &size) const
{
    //COWTODO(n2omatt): Make sure that images and rects are the same size.

    //Build the Frames.
    QVariantMap frames_map;
    for(int i = 0; i < images.size(); ++i)
    {
        auto image = images[i];
        auto rect  = rects [i];

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
    metadata_map["realTextureFileName"] = m_outputPath;
    metadata_map["textureFileName"    ] = m_outputPath;
    metadata_map["size"               ] = QString().sprintf(
        "{%d, %d}",
        size.width(),
        size.height()
    );

    //Build the Plist.
    QVariantMap plist_map;
    plist_map["frames"  ] = frames_map;
    plist_map["metadata"] = metadata_map;

    //Write to file.
    QFile file(m_outputPath);
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QTextStream stream(&file);
        stream << PListSerializer::toPList(plist_map);

        file.close();
    }
}
