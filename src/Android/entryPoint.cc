#pragma clang diagnostic ignored "-Wwritable-strings"
#pragma clang diagnostic ignored "-Wswitch"
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include <jni.h>
#include "basic.hh"
#include "utils.hh"
logType print;
#include "../include.hh"
#include "../box2dInclude.cc"
#include "package.cc"

extern "C" JNIEXPORT s32 JNICALL JNImain(JNIEnv* env, jobject) {
    int a = 6;
    int b = 9;
    int c = a + b;
    return c;
}
