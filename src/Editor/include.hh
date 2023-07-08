#pragma once

#include "../../vendor/imgui/imgui.h"
#include "../../vendor/imgui/backends/imgui_impl_opengl3.h"
#include "../../vendor/imgui/backends/imgui_impl_win32.h"
#include "console.cc"
#include "vision.cc"
#pragma warning(disable: 4312)  //engine->fb.texture is u32 and imgui wants void*
#include "editor.cc"
#pragma warning(default: 4312)
