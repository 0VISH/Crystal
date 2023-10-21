//@ignore
#if(__clang__)
#pragma clang diagnostic ignored "-Wwritable-strings"
#pragma clang diagnostic ignored "-Wswitch"
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif

#define APIENTRY
#define ENGINE true
#define EXPORT extern "C" JNIEXPORT

#include <jni.h>
#include <dlfcn.h>
#include "basic.hh"
#include "utils.hh"
logType print;
#include "../include.hh"
#include "../box2dFiles.cc"
#include "package.cc"

EXPORT int JNICALL JNImain(JNIEnv* env, jobject) {
    void *gameCode = dlopen("gameAnd.so", RTLD_LAZY);
    return EXIT_SUCCESS;
}
