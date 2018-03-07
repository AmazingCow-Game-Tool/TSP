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
    const SheetWriterOptions            &options) const noexcept
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
    auto final_width = (options.size_ForcePOT)
        ? acow::math::ClosestPOT(options.size_SheetNeeded.width)
        : options.size_SheetNeeded.width;

    auto final_height = (options.size_ForcePOT)
        ? acow::math::ClosestPOT(options.size_SheetNeeded.height)
        : options.size_SheetNeeded.height;

    if(options.size_ForceSquare)
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
    auto filename   = options.filename_OutputImage;
    auto outpath    = CoreFS::ExpandUserAndMakeAbs(options.path_Output);
    auto final_path = CoreFS::Join(outpath, {filename});

    final_path = CoreFS::ChangeExtension(final_path, "png");

    if(!CoreFS::IsDir(outpath))
         CoreDir::CreateDirectory(outpath);

    acow::sdl::Surface::Save(final_path, p_surface.get());

    ACOW_SAFE_FREE(p_pixel_data_arr);
    SDL_SetRenderTarget(p_renderer_ref, nullptr);
}
