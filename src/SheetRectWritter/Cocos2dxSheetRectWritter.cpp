//Header
#include "include/SheetRectWritter/Cocos2dxSheetRectWritter.h"


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
    //Empty...
}
