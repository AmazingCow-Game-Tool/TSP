//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : UI.cpp                                                        //
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
#include "include/UI/UI.h"
// std
#include <algorithm>
#include <vector>
#include <string>
// AmazingCow Libs
#include "acow/algo.h"
// TSP
#include "include/UI/private/Logger.h"
#include "include/UI/private/ImGui_Glue.h"
#include "include/Core/Core.h"

// Usings
using namespace TSP;


//----------------------------------------------------------------------------//
// Macros                                                                     //
//----------------------------------------------------------------------------//
#define LOG() UI::Logger()

//----------------------------------------------------------------------------//
// iVars                                                                      //
//----------------------------------------------------------------------------//
// Window / Renderer.
acow_global_variable acow::sdl::Window  ::UPtr m_pWindow  (nullptr, nullptr);
acow_global_variable acow::sdl::Renderer::UPtr m_pRenderer(nullptr, nullptr);
// RenderTexture.
acow_global_variable acow::sdl::Texture::UPtr m_pRenderTexture(nullptr, nullptr);
// Housekeeping.
acow_global_variable Core::RunInfo m_runInfo;
acow_global_variable bool          m_isRunning = false;
// Packing stuff.
acow_global_variable std::vector<Core::Image::SPtr>      m_images;
acow_global_variable Core::IPackingStrategy::UPtr        m_pPackingStrategy;
acow_global_variable Core::IImageSorter::UPtr            m_pSortMethod;
acow_global_variable Core::IPackingStrategy::PackResults m_packResults;

acow_global_variable bool m_packIsDirty = true;


//----------------------------------------------------------------------------//
// Image Functions                                                            //
//----------------------------------------------------------------------------//
acow_internal_function void
image_load(const std::string &path) noexcept
{
    auto it = acow::algo::find_if(
        m_images,
        [&path](Core::Image::SPtr &pImage) {
            return (pImage->GetPath() == path);
        }
    );

    // Already has this image...
    if(it != std::end(m_images))
    {
        LOG()->Info(
            "Image already loaded - Path: (%s)",
            (*it)->GetPath()
        );
        return;
    }

    // Load the image.
    LOG()->Debug("Loading image - Path: (%s)", path);
    auto p_image = Core::ImageLoader().LoadImage(path);
    m_images.push_back(p_image);

    m_packIsDirty = true;
}

acow_internal_function void
image_unload(const std::string &path) noexcept
{
    auto it = acow::algo::find_if(
        m_images,
        [&path](Core::Image::SPtr pImage) {
            return (pImage->GetPath() == path);
        }
    );

    // Not found.
    COREASSERT_ASSERT(
        it == std::end(m_images),
        "Removing a invalid image - Path: (%s)",
        path.c_str()
    );

    // Remove and reorganize the container.
    m_images.erase(it);

    m_packIsDirty = true;
}

acow_internal_function void
image_sort() noexcept
{
    COREASSERT_ASSERT(m_pSortMethod, "m_pSortMethod can't be null");

    auto p_method_raw = m_pSortMethod.get();
    acow::algo::sort(
        m_images,
        [p_method_raw](
            const Core::Image::SPtr &i1,
            const Core::Image::SPtr &i2)
        {
            return (m_pSortMethod->Sort(i1, i2) > 0);
        }
    );
}


//----------------------------------------------------------------------------//
// Pack Functions                                                             //
//----------------------------------------------------------------------------//
acow_internal_function void
pack_set_sort_method(const std::string &name) noexcept
{
    LOG()->Info("Changing Sort Method - Name: (%s)", name);
    m_pSortMethod = Core::ImageSorterFactory::CreateUnique(name);
}

acow_internal_function void
pack_set_packing_strategy(const std::string &name) noexcept
{
    // COWTODO(n2omatt): Create the packing factory...
    LOG()->Info("Changing Packing Strategy - Name (%s)", name);
    m_pPackingStrategy = acow::make_unique<Core::SimplePackingStrategy>();
}

acow_internal_function void
pack_run()
{
    //--------------------------------------------------------------------------
    // Sanity checks.
    COREASSERT_ASSERT(m_pPackingStrategy, "m_pPackingStrategy can't be null");
    COREASSERT_ASSERT(m_pSortMethod,      "m_pSortMethod can't be null"     );

    LOG()->Debug("Packing...");

    m_packResults = m_pPackingStrategy->Pack(m_images);
    m_packIsDirty = false;

    LOG()->Info(
        "Packing results - Rects: (%d) - Size: (%.1f,%.1f)",
        m_packResults.rects.size(),
        m_packResults.sheet_Size.GetWidth (),
        m_packResults.sheet_Size.GetHeight()
    );
}


//----------------------------------------------------------------------------//
// Directory Functions                                                        //
//----------------------------------------------------------------------------//
acow_internal_function void
directory_add(
    const std::string              &path,
    const std::vector<std::string> &allowedExtensions) noexcept
{
    auto finder      = Core::DirectoryImageFinder({path}, allowedExtensions);
    auto found_paths = finder.FindImagesPaths();

    acow::algo::for_each(found_paths, [](const std::string &path){
        image_load(path);
    });

    m_packIsDirty = true;
}

//----------------------------------------------------------------------------//
//  Render Functions                                                          //
//----------------------------------------------------------------------------//
acow_internal_function acow::sdl::Texture::UPtr
render_create_texture(int width, int height) noexcept
{
    LOG()->Debug("Creating new texture - Size: (%d, %d)", width, height);

    //--------------------------------------------------------------------------
    // Constants.
    acow_local_persist auto kTextureFormat = SDL_PIXELFORMAT_RGBA8888;
    acow_local_persist auto kTextureAccess = SDL_TEXTUREACCESS_TARGET;

    //--------------------------------------------------------------------------
    // Create the texture.
    auto p_texture = acow::sdl::Texture::CreateUnique(
        m_pRenderer.get(),
        kTextureFormat,
        kTextureAccess,
        width,
        height
    );

    return p_texture;
}


acow_internal_function void
render_render_packed_images()
{
    LOG()->Debug("Rendering packed images.");

    //--------------------------------------------------------------------------
    // Sanity checks...
    COREASSERT_ASSERT(
        m_images.size() == m_packResults.rects.size(),
        "Size mismatch - images: (%d) - rects: (%d)",
        m_images.size(),
        m_packResults.rects.size()
    );

    //--------------------------------------------------------------------------
    // Compute the final size of image.
    auto final_width  = m_packResults.sheet_Size.width;
    auto final_height = m_packResults.sheet_Size.height;

    if(m_runInfo.sheet_ForcePOT)
    {
        final_width  = acow::math::ClosestPOT(unsigned(final_width ));
        final_height = acow::math::ClosestPOT(unsigned(final_height));
    }

    if(m_runInfo.sheet_ForceSquare)
    {
        final_width = final_height = acow::math::Max(final_width, final_height);
    }

    //--------------------------------------------------------------------------
    // Create the Intermediate Texture.
    m_pRenderTexture = render_create_texture(final_width, final_height);

    //--------------------------------------------------------------------------
    // "Blit" the textures together.
    auto p_renderer_raw = m_pRenderer.get();
    SDL_SetRenderTarget(p_renderer_raw, m_pRenderTexture.get());
    SDL_RenderClear(p_renderer_raw);

    const auto images_size = m_images.size();
    for(int i = 0; i < images_size; ++i)
    {
        auto p_image = m_images[i];
        COREASSERT_ASSERT(p_image, "p_image can't be null");

        auto p_texture = p_image->GetTexture();
        COREASSERT_ASSERT(p_texture, "p_texture can't be null");

        auto rect = m_packResults.rects[i];
        COREASSERT_ASSERT(!rect.IsEmpty(), "rect can't be empty.");

        auto src_rect = SDL_Rect {
            0,
            0,
            int(rect.GetWidth()),
            int(rect.GetHeight())
        };
        auto dst_rect = (SDL_Rect)rect;

        SDL_RenderCopy(p_renderer_raw, p_texture, &src_rect, &dst_rect);
    }

    SDL_RenderPresent(p_renderer_raw);
    SDL_SetRenderTarget(p_renderer_raw, nullptr);
}


//----------------------------------------------------------------------------//
// UI Functions                                                               //
//----------------------------------------------------------------------------//
acow_internal_function std::string
ui_build_window_caption() noexcept
{
    // COWTODO(n2omatt): refactor
    return "TSP - AmazingCow - 0.1.0";
}

acow_internal_function void
ui_handle_events() noexcept
{
    acow_local_persist SDL_Event s_event {};
    while(SDL_PollEvent(&s_event))
    {
        UI::imgui_HandleEvent(&s_event);
        if(s_event.type == SDL_QUIT)
            m_isRunning = false;
    }
}

acow_internal_function void
ui_update() noexcept
{
    if(m_packIsDirty)
    {
        image_sort                 ();
        pack_run                   ();
        render_render_packed_images();
    }

    UI::imgui_Update();
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f


        if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}

acow_internal_function void
ui_render() noexcept
{
    UI::imgui_PreRender();
    // SDL_SetRenderDrawColor(m_pRenderer.get(),  255, 255, 255, 255);
    // SDL_RenderClear(m_pRenderer.get());
    if(m_pRenderTexture)
    {
        auto size = acow::sdl::Texture::QuerySize(m_pRenderTexture.get());
        auto src_rect = (SDL_Rect)(
            acow::math::Rect(0, 0, size.GetWidth(), size.GetHeight())
        );
        SDL_RenderCopy(
            m_pRenderer.get(),
            m_pRenderTexture.get(),
            &src_rect,
            &src_rect
        );
    }
    SDL_RenderPresent(m_pRenderer.get());

    UI::imgui_PostRender();
}


//----------------------------------------------------------------------------//
// Init / Shutdown                                                            //
//----------------------------------------------------------------------------//
void
UI::InitLean()
{
    //--------------------------------------------------------------------------
    // Only initialize once...
    acow_local_persist auto s_lean_inited = false;
    if(s_lean_inited)
        return;

    s_lean_inited = true;

    //--------------------------------------------------------------------------
    // Init subsystems.
    Logger()->D("Initializing subsystems.");
    acow::sdl::Init(SDL_INIT_EVERYTHING);
    acow::sdl::img::Init(IMG_INIT_JPG | IMG_INIT_PNG);
    acow::sdl::ttf::Init();

    //--------------------------------------------------------------------------
    // Create Window.
    Logger()->D("Creating Window.");
    m_pWindow = acow::sdl::Window::CreateUnique(
        ui_build_window_caption(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL
    );

    //--------------------------------------------------------------------------
    // Create Renderer.
    Logger()->D("Creating Renderer.");
    m_pRenderer = acow::sdl::Renderer::CreateUnique(m_pWindow.get(), -1, 0);
}

void
UI::Init(const Core::RunInfo &runInfo) noexcept
{
    InitLean();
    SDL_ShowWindow(m_pWindow.get());

    m_runInfo = runInfo;

    imgui_Init(m_pWindow.get());

    //--------------------------------------------------------------------------
    // Pre load the images.
    for(const auto &dir_images : runInfo.dirs_Images)
        directory_add(dir_images, runInfo.dirs_ImagesAllowedExtensions);

    //--------------------------------------------------------------------------
    // Set Pack stuff.
    pack_set_packing_strategy("COWTODO");
    pack_set_sort_method     (runInfo.pack_SortType);
}

void
UI::Shutdown() noexcept
{
    Logger()->D("Shutting down.");
}


//----------------------------------------------------------------------------//
// Lifecycle                                                                  //
//----------------------------------------------------------------------------//
void
UI::Run() noexcept
{
    m_isRunning = true;
    while(m_isRunning)
    {
        ui_handle_events();
        ui_update       ();
        ui_render       ();
    }
}


//----------------------------------------------------------------------------//
// Helper Methods                                                             //
//----------------------------------------------------------------------------//
SDL_Renderer*
UI::GetRendererRef() noexcept
{
    COREASSERT_ASSERT(m_pRenderer, "m_pRenderer can't be null");
    return m_pRenderer.get();
}