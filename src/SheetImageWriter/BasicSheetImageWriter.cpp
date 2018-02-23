// Header
#include "include/SheetImageWriter/Implementation/BasicSheetImageWriter.h"


//----------------------------------------------------------------------------//
// Interface Methods                                                          //
//----------------------------------------------------------------------------//
void BasicSheetImageWriter::Write(
    const SheetWriterOptions &options) const noexcept
{
    // //Put all the images into the final image.
    // QImage   sheet_image(options.sheetSize, QImage::Format_RGBA8888);
    // QPainter painter    (&sheet_image);

    // for(int i = 0; i < options.images.size(); ++i)
    // {
    //     const auto &src_image = options.images[i];
    //     const auto &src_rect  = options.rects [i];

    //     painter.drawImage(src_rect, src_image.getQImage());
    // }

    // painter.end();


    // //Save the image.
    // auto filename   = options.imageOutputFilename;
    // auto outpath    = options.outputPath;
    // auto final_path = QDir(outpath).filePath(filename);

    // sheet_image.save(final_path);
}
