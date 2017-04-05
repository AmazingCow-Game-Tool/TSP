//Header
#include "include/ImageLoader.h"


////////////////////////////////////////////////////////////////////////////////
// CTOR                                                                       //
////////////////////////////////////////////////////////////////////////////////
ImageLoader::ImageLoader(const QVector<QString> &imagePaths) :
    m_imagePaths(imagePaths)
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
QVector<Image> ImageLoader::loadImages()
{
    QVector<Image> images;
    foreach(QString path, m_imagePaths)
    {
        auto image = Image::LoadFromFile(path);
        images.push_back(image);
    }

    return images;
}

