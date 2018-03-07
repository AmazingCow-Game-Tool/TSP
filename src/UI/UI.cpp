// Header
#include "include/UI/UI.h"
// TSP
#include "include/UI/private/Logger.h"

// Usings
using namespace TSP;

//----------------------------------------------------------------------------//
// iVars                                                                      //
//----------------------------------------------------------------------------//
// Window / Renderer.
acow_global_variable acow::sdl::Window  ::UPtr m_pWindow  (nullptr, nullptr);
acow_global_variable acow::sdl::Renderer::UPtr m_pRenderer(nullptr, nullptr);
// RenderTexture
acow_global_variable SDL_Texture *m_pRenderTexture = nullptr;
// Housekeeping.
acow_global_variable bool m_isRunning = false;


//----------------------------------------------------------------------------//
// Private Function                                                           //
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
        if(s_event.type == SDL_QUIT)
            m_isRunning = false;
    }
}

acow_internal_function void
ui_update() noexcept
{

}

acow_internal_function void
ui_render() noexcept
{
    SDL_RenderClear(m_pRenderer.get());

    SDL_RenderPresent(m_pRenderer.get());
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
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN
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
// Helper Functions                                                           //
//----------------------------------------------------------------------------//
SDL_Renderer*
UI::GetRendererRef() noexcept
{
    COREASSERT_ASSERT(
        m_pRenderer,
        "UI isn't initialized yet - Call UI::InitLean first."
    );

    return m_pRenderer.get();
}