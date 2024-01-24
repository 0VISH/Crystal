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

EXPORT void JNICALL Java_com_example_androidcrystal_MainActivity_CrystalInit(JNIEnv* env, jobject obj, jobject assetManager){
    mem::init();
    Package::assetManager = AAssetManager_fromJava(env, assetManager);
#if(DBG)
    print = dlog;
#else
#endif
    engine = (Crystal*)mem::alloc(sizeof(Crystal));
    engine->init();
    engine->windowX = 0;
    engine->windowY = 0;
    engine->gameCode = dlopen("libgameand.so", RTLD_LAZY);
    GET_POINTERS(engine->gameCode);
    SET_POINTERS;
    engine->gameLayerOff = engine->lm.layerCount;
    engine->lm.newLayer();
    Layer *gameLayer = &engine->lm.layers[engine->gameLayerOff];
    gameLayer->onUpdate = GameLayer::onUpdate;
    gameLayer->onRender = GameLayer::onRender;
    gameLayer->onUninit = GameLayer::onUninit;
    auto gameInit = (void(*)())dlsym(engine->gameCode, "init");
    gameInit();
}
EXPORT void JNICALL Java_com_example_androidcrystal_MainActivity_CrystalUninit(JNIEnv* env, jobject obj){
    dlclose(engine->gameCode);
    engine->uninit();
    mem::free(engine);
};
unsigned int VBO, VAO, EBO;
EXPORT void JNICALL Java_com_example_androidcrystal_Renderer_CrystalSurfaceCreated(JNIEnv* env, jobject obj){
    engine->initGraphics();
    print("Render context: %s\n", Draw::getRenderContextInfoString());
    sq = Draw::initScreenQuad();
    screenShader = engine->ss.newShader("package/shader/glsl3es/displayVertex.glsl", "package/shader/glsl3es/displayFragment.glsl", "display");
};
EXPORT void JNICALL Java_com_example_androidcrystal_Renderer_CrystalSurfaceChanged(JNIEnv* env, jobject obj, jint x, jint y){
    engine->windowX = x;
    engine->windowY = y;
    glViewport(0, 0, x, y);
    engine->fb.init(x, y);
};
EXPORT void JNICALL Java_com_example_androidcrystal_Renderer_CrystalUpdate(JNIEnv* env, jobject obj){
    Event e;
    f64 dt = 0.1;
    e.type = EventType::NONE;
    engine->lm.updateLayers(e, dt);
};

EXPORT void JNICALL Java_com_example_androidcrystal_Renderer_CrystalDraw(JNIEnv* env, jobject obj){
    engine->lm.renderLayers();
    
    Draw::beginFrame(engine->r, engine->fb);
    Draw::draw(engine->r);
    Draw::endFrame(engine->r, engine->fb);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    Shader::useShader(screenShader);
    glBindVertexArray(sq.vao);
    glBindTexture(GL_TEXTURE_2D, engine->fb.texture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
};
