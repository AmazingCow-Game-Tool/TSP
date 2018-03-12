#pragma once
// ImGui
#include "imgui/imgui.h"
// AmazingCow Libs
#include "acow/sdl_goodies.h"

namespace TSP { namespace UI {

void imgui_Init       (SDL_Window *pWindowRef) noexcept;
void imgui_HandleEvent(SDL_Event  *pEvent    ) noexcept;
void imgui_Update     ()                       noexcept;
void imgui_PreRender  ()                       noexcept;
void imgui_PostRender ()                       noexcept;
void imgui_Shutdown   ()                       noexcept;

} // namespace UI
} // namespace TSP
