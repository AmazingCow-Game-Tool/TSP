// Header
#include "include/Image.h"


//----------------------------------------------------------------------------//
// Static Methods                                                             //
//----------------------------------------------------------------------------//
Image Image::LoadFromFile(const std::string &filePath)
{
    Image img;
    // img.m_image = QImage(filePath);
    // img.m_size = img.m_image.size();
    // img.m_path = filePath;

    return img;
}

//----------------------------------------------------------------------------//
// Public Methods                                                             //
//----------------------------------------------------------------------------//
const std::string& Image::GetPath() const noexcept
{
    return m_path;
}

const std::string Image::GetBasename() const noexcept
{
    // return QFileInfo(m_path).baseName();
}

const std::string Image::GetFilename() const noexcept
{
    // return QFileInfo(m_path).fileName();
}

const acow::math::Size& Image::GetSize() const noexcept
{
    return m_size;
}
