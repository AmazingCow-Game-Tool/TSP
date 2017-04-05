//Header
#include "include/SheetImageWritter/BasicSheetImageWritter.h"
//QT
#include <QtGui>


////////////////////////////////////////////////////////////////////////////////
// CTOR                                                                       //
////////////////////////////////////////////////////////////////////////////////
BasicSheetImageWritter::BasicSheetImageWritter(const QString &outputPath) :
    m_outputPath(outputPath)
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Interface Methods                                                          //
////////////////////////////////////////////////////////////////////////////////
void BasicSheetImageWritter::write(
    const QVector<Image> &images,
    const QVector<QRect> &rects,
    const QSize          &size) const
{
    QImage   sheet_image(size, QImage::Format_RGBA8888);
    QPainter painter    (&sheet_image);

    for(int i = 0; i < images.size(); ++i)
    {
        const auto &src_image = images[i];
        const auto &src_rect  = rects [i];

        painter.drawImage(src_rect, src_image.getQImage());
    }

    painter.end();

    sheet_image.save(m_outputPath);
}
