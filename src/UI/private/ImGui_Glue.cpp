// Header
#include "include/UI/private/ImGui_Glue.h"
// SDL
#include <SDL_opengl.h>
// ImGui
#include "imgui/examples/sdl_opengl2_example/imgui_impl_sdl_gl2.h"
// Amazing Cow Libs
#include "CoreAssert/CoreAssert.h"

// Usings
using namespace TSP;


//----------------------------------------------------------------------------//
// Vars                                                                       //
//----------------------------------------------------------------------------//
acow_global_variable SDL_GLContext    g_pGLContext = nullptr;
acow_global_variable SDL_Window      *g_pWindowRef = nullptr;
acow_global_variable acow::sdl::Color g_ClearColor = acow::sdl::Color::CornflowerBlue();

//----------------------------------------------------------------------------//
// Functions                                                                  //
//----------------------------------------------------------------------------//
void UI::imgui_Init(SDL_Window *pWindowRef) noexcept
{
    COREASSERT_ASSERT(pWindowRef, "pWindowRef can't be null");
    g_pWindowRef = pWindowRef;

    //--------------------------------------------------------------------------
    // Setup OpenGL.
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,           1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,            24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE,           8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,  2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,  2);

    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);

    g_pGLContext = SDL_GL_CreateContext(pWindowRef);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // COWTODO(n2omatt): Assert if inited correctly...

    //--------------------------------------------------------------------------
    // Setup ImGui binding.
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    ImGui_ImplSdlGL2_Init(pWindowRef);

    //--------------------------------------------------------------------------
    // Setup style.
    ImGui::StyleColorsDark();
}

void UI::imgui_HandleEvent(SDL_Event *pEvent) noexcept
{
    COREASSERT_ASSERT(pEvent, "pEvent can't be null");
    ImGui_ImplSdlGL2_ProcessEvent(pEvent);
}

void UI::imgui_Update() noexcept
{
    ImGui_ImplSdlGL2_NewFrame(g_pWindowRef);
}

void UI::imgui_PreRender() noexcept
{
    //--------------------------------------------------------------------------
    // OpenGL.
    u32 width  = ImGui::GetIO().DisplaySize.x;
    u32 height = ImGui::GetIO().DisplaySize.y;

    glViewport(
        0,
        0,
        (int)ImGui::GetIO().DisplaySize.x,
        (int)ImGui::GetIO().DisplaySize.y
    );

    glClearColor(g_ClearColor.r, g_ClearColor.g, g_ClearColor.b, g_ClearColor.a);
    glClear     (GL_COLOR_BUFFER_BIT);
}

void UI::imgui_PostRender() noexcept
{
    //--------------------------------------------------------------------------
    // ImGui.
    ImGui::Render();
    ImGui_ImplSdlGL2_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(g_pWindowRef);
}

void UI::imgui_Shutdown() noexcept
{
    if(!g_pGLContext)
        return;

    //--------------------------------------------------------------------------
    // ImGui.
    ImGui_ImplSdlGL2_Shutdown();
    ImGui::DestroyContext    ();

    //--------------------------------------------------------------------------
    // OpenGL.
    SDL_GL_DeleteContext(g_pGLContext);
    g_pGLContext = nullptr;
}
