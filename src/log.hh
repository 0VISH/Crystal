#pragma once

#include <stdarg.h>
#include <stdio.h>

void initLogOutputFile(char *fileName);
void closeLogOutputFile();
void dlog(const char *fmt, ...);
void log(const char *fmt, ...);
