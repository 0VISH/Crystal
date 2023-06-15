#define IMGUI_IMPLEMENTATION
#define IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_ENABLE_FREETYPE

#include "../config.hh"

#include "../../vendor/imgui/misc/single_file/imgui_single_file.h"
#include "../../vendor/imgui/backends/imgui_impl_win32.cpp"

#if(RCONTEXT_GL)
#include "../../vendor/imgui/backends/imgui_impl_opengl3.cpp"
#endif
