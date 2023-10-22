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
#include "include.hh"

EXPORT void JNICALL Java_com_example_androidcrystal_MainActivity_CrystalInit(JNIEnv* env, jobject obj){
#if(DBG)
    print = dlog;
#else
#endif
    engine = (Crystal*)mem::alloc(sizeof(Crystal));
    //engine->init();
    engine->gameCode = dlopen("libgameand.so", RTLD_LAZY);
}
EXPORT void JNICALL Java_com_example_androidcrystal_MainActivity_CrystalUninit(JNIEnv* env, jobject obj){
    //engine->uninit();
    mem::free(engine);
};
EXPORT void JNICALL Java_com_example_androidcrystal_Renderer_CrystalDraw(JNIEnv* env, jobject obj){
    glClearColor(0.1f, 0.5f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
};
