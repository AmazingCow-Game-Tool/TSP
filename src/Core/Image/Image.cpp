// Header
#include "include/Core/Image/Image.h"
// AmazingCow Libs
#include "CoreAssert/CoreAssert.h"
#include "acow/sdl_goodies.h"
// TSP
#include "include/UI/UI.h"
#include "include/Core/private/Logger.h"

// Usings
using namespace TSP;
using namespace Core;


//----------------------------------------------------------------------------//
// Static Methods                                                             //
//----------------------------------------------------------------------------//
Image::SPtr Image::LoadFromFile(const std::string &filePath)
{
    UI::InitLean(); // Make sure that SDL is initialized.

    //--------------------------------------------------------------------------
    // Canonize the path.
    auto fullpath = CoreFS::ExpandUserAndMakeAbs(filePath);

    //--------------------------------------------------------------------------
    // Load Image
    auto p_texture = acow::sdl::Texture::LoadFromFile(
        fullpath,
        UI::GetRendererRef()
    );

    //--------------------------------------------------------------------------
    // Setup the object.
    auto p_image = std::make_shared<Image>();
    p_image->m_pTexture = p_texture;
    p_image->m_size     = acow::sdl::Texture::QuerySize(p_texture);
    p_image->m_path     = fullpath;

    //--------------------------------------------------------------------------
    // Log.
    Core::Logger()->Debug(
        "Loaded image - Path: (%s) - Size: (%.1f, %.1f)",
        p_image->m_path,
        p_image->m_size.GetWidth(),
        p_image->m_size.GetHeight()
    );

    return p_image;
}


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
Image::~Image()
{
    COREASSERT_ASSERT(
        m_pTexture,
        "Invalid dealocation - m_pTexture can't be null"
    );

    Core::Logger()->Debug("Releasing texture of image - Path: (%s)", m_path);
    ACOW_SDL_SAFE_DESTROY_TEXTURE(m_pTexture);
}
