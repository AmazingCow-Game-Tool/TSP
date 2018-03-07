// Header
#include "include/Core/Image/Image.h"
// AmazingCow Libs
#include "CoreAssert/CoreAssert.h"
#include "acow/sdl_goodies.h"
// TSP
#include "include/UI/UI.h"

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

    return p_image;
}


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
Image::~Image()
{
    ACOW_SDL_SAFE_DESTROY_TEXTURE(m_pTexture);
}
