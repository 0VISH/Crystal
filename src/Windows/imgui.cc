#define IMGUI_IMPLEMENTATION
#define IMGUI_DEFINE_MATH_OPERATORS

#include "misc/single_file/imgui_single_file.h"
#include "backends/imgui_impl_win32.cpp"

#if(RCONTEXT_GL)
#include "backends/imgui_impl_opengl3.cpp"
#endif
