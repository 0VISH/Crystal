//change this while compiling to android
#define GAME_SRC   "../../sandbox/src/include.hh"
//-----------------------------------------------

#define ENGINE true
#define APIENTRY

#pragma clang diagnostic ignored "-Wwritable-strings"
#pragma clang diagnostic ignored "-Wswitch"
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include <jni.h>
#include "basic.hh"
#include "utils.hh"
logType print;
#include "checks.hh"
#include "../include.hh"
#include "../box2dFiles.cc"
#include "package.cc"

#include GAME_SRC

extern "C" JNIEXPORT s32 JNICALL JNImain(JNIEnv* env, jobject) {
    int a = 6;
    int b = 9;
    int c = a + b;
    return c;
}
