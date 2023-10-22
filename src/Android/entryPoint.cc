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
#include <android/log.h>
#include "basic.hh"
#include "utils.hh"
logType print;
#include "../include.hh"
#include "../box2dFiles.cc"
#include "include.hh"

EXPORT int JNICALL Java_com_example_androidcrystal_MainActivity_CrystalMain(JNIEnv* env, jobject obj, jobject surface) {
#if(DBG)
    print = dlog;
#else
#endif
    Frontend fr = createFrontend(env, surface);
    engine = (Crystal*)mem::alloc(sizeof(Crystal));
    //engine->init();
    engine->gameCode = dlopen("libgameand.so", RTLD_LAZY);

    glClearColor(0.1f, 0.5f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //engine->uninit();
    mem::free(engine);
    deleteFrontend(fr);
    return EXIT_SUCCESS;
}
