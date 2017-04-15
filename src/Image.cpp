//Header
#include "include/Image.h"


////////////////////////////////////////////////////////////////////////////////
// Static Methods //
////////////////////////////////////////////////////////////////////////////////
Image Image::LoadFromFile(const QString &filePath)
{
    Image img;
    img.m_image = QImage(filePath);
    img.m_size = img.m_image.size();
    img.m_path = filePath;

    return img;
}

////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
const QString& Image::getPath() const
{
    return m_path;
}

const QString Image::getBasename() const
{
    return QFileInfo(m_path).baseName();
}

const QString Image::getFilename() const
{
    return QFileInfo(m_path).fileName();
}

const QSize& Image::getSize() const
{
    return m_size;
}

const QImage& Image::getQImage() const
{
    return m_image;
}
