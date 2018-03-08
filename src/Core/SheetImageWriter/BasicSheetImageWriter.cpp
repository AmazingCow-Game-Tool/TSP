//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : BasicSheetImageWriter.cpp                                     //
//  Project   : TSP                                                           //
//  Date      : Mar 07, 2018                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2018                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// Header
#include "include/Core/SheetImageWriter/Implementation/BasicSheetImageWriter.h"
// AmazingCow Libs
#include "CoreFS/CoreFS.h"
#include "CoreDir/CoreDir.h"
#include "acow/math_goodies.h"
// TSP
#include "include/UI/UI.h"

// Usings
using namespace TSP;
using namespace Core;


//----------------------------------------------------------------------------//
// Interface Methods                                                          //
//----------------------------------------------------------------------------//
void
BasicSheetImageWriter::Write(
    const std::vector<Image::SPtr>      &images,
    const std::vector<acow::math::Rect> &rects,
    const acow::math::Size              &sheetSizeNeeded,
    bool                                 forcePOT,
    bool                                 forceSquare,
    const std::string                   &outputFullpath) const noexcept
{
    //--------------------------------------------------------------------------
    // Sanity checks...
    COREASSERT_ASSERT(
        images.size() == rects.size(),
        "Size mismatch - images: (%d) - rects: (%d)",
        images.size(),
        rects.size()
    );

    UI::InitLean(); // Make sure that SDL is initialized.
    auto p_renderer_ref = UI::GetRendererRef();

    //--------------------------------------------------------------------------
    // Compute the final size of image.
    auto final_width = (forcePOT)
        ? acow::math::ClosestPOT(sheetSizeNeeded.width)
        : sheetSizeNeeded.width;

    auto final_height = (forcePOT)
        ? acow::math::ClosestPOT(sheetSizeNeeded.height)
        : sheetSizeNeeded.height;

    if(forceSquare)
        final_width = final_height = acow::math::Max(final_width, final_height);

    //--------------------------------------------------------------------------
    // Create the texture.
    auto texture_format = SDL_PIXELFORMAT_RGBA8888;
    auto texture_access = SDL_TEXTUREACCESS_TARGET;

    auto p_texture = acow::sdl::Texture::CreateUnique(
        p_renderer_ref,
        texture_format,
        texture_access,
        final_width,
        final_height
    );

    //--------------------------------------------------------------------------
    // Blit the textures together.
    SDL_SetRenderTarget(p_renderer_ref, p_texture.get());
    for(int i = 0; i < images.size(); ++i)
    {
        auto p_image = images[i];
        COREASSERT_ASSERT(p_image, "p_image can't be null");

        auto p_texture = p_image->GetTexture();
        COREASSERT_ASSERT(p_texture, "p_texture can't be null");

        auto rect = rects[i];
        COREASSERT_ASSERT(!rect.IsEmpty(), "rect can't be empty.");

        auto src_rect = (SDL_Rect)rect;
        auto dst_rect = (SDL_Rect)rect;

        SDL_RenderCopy(p_renderer_ref, p_texture, &src_rect, &dst_rect);
    }

    //--------------------------------------------------------------------------
    // Get the rendered pixels to make the output image.
    auto bytes_per_pixel   = 4;
    void *p_pixel_data_arr = malloc(final_width * final_height * bytes_per_pixel);

    auto texture_pitch = final_width * bytes_per_pixel;
    SDL_RenderReadPixels(
        p_renderer_ref,
        nullptr,
        texture_format,
        p_pixel_data_arr,
        texture_pitch
    );

    auto p_surface = acow::sdl::Surface::CreateUnique(
        p_pixel_data_arr,
        final_width,
        final_height,
        bytes_per_pixel,
        texture_pitch,
        texture_format
    );

    //--------------------------------------------------------------------------
    // Save the image.
    acow::sdl::Surface::Save(outputFullpath, p_surface.get());

    //--------------------------------------------------------------------------
    // Free the resources.
    ACOW_SAFE_FREE(p_pixel_data_arr);
    SDL_SetRenderTarget(p_renderer_ref, nullptr);
}
