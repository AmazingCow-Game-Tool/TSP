#pragma once

//QT
#include <QtCore>
//TSP
#include "include/Image.h"

struct SheetWritterOptions
{
    QString imageOutputFilename;
    QString dataOutputFilename;

    QString outputPath;

    QVector<Image> images;
    QVector<QRect> rects;

    QSize sheetSize;
};
