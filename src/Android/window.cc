#include <EGL/egl.h>
#include <android/native_window_jni.h>

struct Frontend{
    EGLDisplay           display;
    EGLContext           context;
    EGLSurface           surface;
    EGLNativeWindowType  window;
};
static EGLint const attribute_list[] = {
    EGL_RED_SIZE, 1,
    EGL_GREEN_SIZE, 1,
    EGL_BLUE_SIZE, 1,
    EGL_NONE
};

Frontend createFrontend(JNIEnv *env, jobject surface){
    Frontend fr;
    
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, NULL, NULL);
    EGLConfig config;
    EGLint num_config;
    eglChooseConfig(display, attribute_list, &config, 1, &num_config);
    fr.context = eglCreateContext(display, config, EGL_NO_CONTEXT, NULL);
    fr.window  = (EGLNativeWindowType)ANativeWindow_fromSurface(env, surface);
    fr.surface = eglCreateWindowSurface(display, config, fr.window, NULL);
    eglMakeCurrent(display, fr.surface, fr.surface, fr.context);
    
    return fr;
};
void deleteFrontend(Frontend &fr){
    eglDestroySurface(fr.display, fr.surface); 
    eglDestroyContext(fr.display, fr.context);
    eglTerminate(fr.display);
};
