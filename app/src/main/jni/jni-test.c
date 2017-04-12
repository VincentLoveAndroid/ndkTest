#include <jni.h>
#include <string.h>

JNIEXPORT jstring JNICALL
Java_com_example_administrator_ndktest_jnitest_JNITest_getStringFromC(JNIEnv *env, jclass type) {

    // TODO
    jstring newString = (*env)->NewStringUTF(env, "我是从c那里过来的String");

    return newString;
}

JNIEXPORT jstring JNICALL
Java_com_example_administrator_ndktest_jnitest_JNITest_getStringFromObject(JNIEnv *env,
                                                                           jobject instance) {

    jclass clz = (*env)->GetObjectClass(env, instance);
    //获取属性的id
    jfieldID fieldID = (*env)->GetFieldID(env, clz, "name", "Ljava/lang/String;");
    //获取属性对应的值
    jstring jstring1 = (*env)->GetObjectField(env, instance, fieldID);
    //jString->c字符串
    const char *cString = (*env)->GetStringUTFChars(env, jstring1, JNI_FALSE);//这里传null,或JNI_FALSE都可以，但是传JNI_TRUE不可以
    char text[50] = " c改变了java object变量的值哦";
    //拼接字符串
    strcat(text, cString);
    jstring newString = (*env)->NewStringUTF(env, text);
    //改变对象的属性
    (*env)->SetObjectField(env, instance, fieldID, newString);
    return newString;
}