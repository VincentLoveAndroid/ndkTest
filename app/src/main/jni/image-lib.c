#include <jni.h>
#include <android/bitmap.h>
#include <stdlib.h>


JNIEXPORT jintArray JNICALL
Java_com_example_administrator_ndktest_NdkImageUtil_getImage(JNIEnv *env, jclass type,
                                                             jintArray buffer_, jint width,
                                                             jint height) {
    jint *buffer = (*env)->GetIntArrayElements(env, buffer_, 0);
    float WhiteDegree = 0.2f;
    int argbDegree = WhiteDegree * 255;
    int newSize = width * height;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int color = buffer[width * y + x];
            int a = color >> 24 & 0xff;
            int r = color >> 16 & 0xff;
            int g = color >> 8 & 0xff;
            int b = color & 0xff;
            r += argbDegree;
            g += argbDegree;
            b += argbDegree;
            //边界处理
            r = r > 255 ? 255 : (r < 0 ? 0 : r);
            g = g > 255 ? 255 : (g < 0 ? 0 : g);
            b = b > 255 ? 255 : (b < 0 ? 0 : b);
            int newColor = (a << 24) | (r << 16) | (g << 8) | b;//合成新颜色值
            buffer[width * y + x] = newColor;
        }
    }
    //指针转jint
    jintArray result = (*env)->NewIntArray(env, newSize);
    (*env)->SetIntArrayRegion(env, result, 0, newSize, buffer);
    (*env)->ReleaseIntArrayElements(env, buffer_, buffer, 0);
    return result;
}