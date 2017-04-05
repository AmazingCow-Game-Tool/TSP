#pragma once

//QT
#include <QtCore>
//TSP
#include "Image.h"

class ImageLoader
{
    // CTOR//
public:
    ImageLoader(const QVector<QString> &imagePaths);


    // Public Methods //
public:
    QVector<Image> loadImages();


    // iVars //
public:
    QVector<QString> m_imagePaths;
};
