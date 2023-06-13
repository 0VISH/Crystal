#pragma once

#include <stdarg.h>
#include <stdio.h>

void initLogOutputFile(char *fileName);
void closeLogOutputFile();
void log(const char *fmt, ...);
void _dlog(char *file, u32 line, const char *fmt, ...);

#define dlog(fmt, ...) _dlog(__FILE__, __LINE__, fmt, __VA_ARGS__);
