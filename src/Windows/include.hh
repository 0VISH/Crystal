#pragma once

#pragma warning(disable: 4005) //glad.h redifines APIENTRY
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma warning(default: 4005)
#include "log.cc"
#include "window.cc"
#include "context.cc"
#include "package.cc"

#include "utilsWin.hh"
#include "code.cc"
