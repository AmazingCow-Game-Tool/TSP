// Header
#include "include/Image/Image.h"
// AmazingCow Libs
#include "CoreAssert/CoreAssert.h"
#include "CoreFS/CoreFS.h"
// stb_image
#ifndef STB_IMAGE_IMPLEMENTATION
    #define STB_IMAGE_IMPLEMENTATION
    #define STBI_FAILURE_USERMSG
#endif
#include "stb_image.h"


//----------------------------------------------------------------------------//
// Static Methods                                                             //
//----------------------------------------------------------------------------//
Image::SPtr Image::LoadFromFile(const std::string &filePath)
{
    //--------------------------------------------------------------------------
    // Canonize the path.
    auto fullpath = CoreFS::ExpandUserAndMakeAbs(filePath);

    //--------------------------------------------------------------------------
    // Load the image from disk.
    int w, h, n;
    uint8_t *p_data = nullptr;

    p_data = stbi_load(fullpath.c_str(), &w, &h, &n, 0);

    COREASSERT_ASSERT(
        p_data,
        "Failed to load image: (%s) - stb_image error: %s",
        fullpath.c_str(),
        stbi_failure_reason()
    );

    //--------------------------------------------------------------------------
    // Setup the object.
    auto p_image = std::make_shared<Image>();
    p_image->m_pData = p_data;
    p_image->m_size  = acow::math::Size(w, h);
    p_image->m_path  = fullpath;


    return p_image;
}


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
Image::~Image()
{
    if(m_pData)
        stbi_image_free(m_pData);
}


//----------------------------------------------------------------------------//
// Public Methods                                                             //
//----------------------------------------------------------------------------//
const std::string& Image::GetPath() const noexcept
{
    return m_path;
}

const std::string Image::GetDirname() const noexcept
{
    return CoreFS::Dirname(m_path);
}

const std::string Image::GetBasename() const noexcept
{
    return CoreFS::Basename(m_path);
}

const acow::math::Size& Image::GetSize() const noexcept
{
    return m_size;
}
