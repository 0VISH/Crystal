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

ScreenQuad sq;
u32 screenShader;

EXPORT void JNICALL Java_com_example_androidcrystal_MainActivity_CrystalInit(JNIEnv* env, jobject obj){
#if(DBG)
    print = dlog;
#else
#endif
    engine = (Crystal*)mem::alloc(sizeof(Crystal));
}
EXPORT void JNICALL Java_com_example_androidcrystal_MainActivity_CrystalUninit(JNIEnv* env, jobject obj){
    dlclose(engine->gameCode);
    //engine->uninit();
    mem::free(engine);
};
EXPORT void JNICALL Java_com_example_androidcrystal_Renderer_CrystalSurfaceCreated(JNIEnv* env, jobject obj){
    //engine->init();
    sq = Draw::initScreenQuad();
    screenShader = engine->ss.newShader("package/shader/displayVertex.glsl", "package/shader/displayFragment.glsl");
    engine->gameCode = dlopen("libgameand.so", RTLD_LAZY);
};
EXPORT void JNICALL Java_com_example_androidcrystal_Renderer_CrystalUpdate(JNIEnv* env, jobject obj){
    Event e = Event::NONE;
    engine->lm.updateLayers(e, dt);
};
EXPORT void JNICALL Java_com_example_androidcrystal_Renderer_CrystalDraw(JNIEnv* env, jobject obj){
    engine->lm.renderLayers();
    Draw::beginFrame(engine->r, engine->fb);
    Draw::draw(engine->r);
    Draw::endFrame(engine->r, engine->fb);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);
  
    Shader::useShader(screenShader);
    glBindVertexArray(sq.vao);
    glBindTexture(GL_TEXTURE_2D, engine->fb.texture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
};
