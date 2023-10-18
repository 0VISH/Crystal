#include <jni.h>

extern "C" JNIEXPORT int JNICALL JNImain(JNIEnv* env, jobject) {
    int a = 6;
    int b = 9;
    int c = a + b;
    return c;
}
