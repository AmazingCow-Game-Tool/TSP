#pragma once

//QT
#include <QtCore>
//TSP
#include "include/SheetImageWritter/ISheetImageWritter.h"


class BasicSheetImageWritter :
    public ISheetImageWritter
{
    // CTOR //
public:
    BasicSheetImageWritter(const QString &outputPath);


    // Interface Methods //
public:
    virtual void write(
        const QVector<Image> &images,
        const QVector<QRect> &rects,
        const QSize          &size
    ) const override;


    // iVars //
private:
    QString m_outputPath;
};
