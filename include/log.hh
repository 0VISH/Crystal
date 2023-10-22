#pragma once

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void initLogOutputFile(char *fileName);
void closeLogOutputFile();
void _log(char *fmt, ...);
void dlog(char *fmt, ...);
