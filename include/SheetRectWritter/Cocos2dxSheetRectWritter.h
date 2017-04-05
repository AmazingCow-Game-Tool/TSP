#pragma once

//QT
#include <QtCore>
//TSP
#include "include/SheetRectWritter/ISheetRectWritter.h"


class Cocos2dxSheetRectWritter :
    public ISheetRectWritter
{
    // CTOR / DTOR //
public:
    Cocos2dxSheetRectWritter(const QString &outputPath);


    // Interface Methods //
public:
    virtual void write(
        const QVector<Image> &images,
        const QVector<QRect> &rects,
        const QSize          &size
    ) const override;


    // iVars //
public:
    QString m_outputPath;
};
