#pragma once

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void initLogOutputFile(char *fileName);
void closeLogOutputFile();
void _log(char *fmt, ...);
void _dlog(char *file, u32 line, const char *fmt, ...);

#define dlog(fmt, ...) _dlog(__FILE__, __LINE__, fmt, __VA_ARGS__);
