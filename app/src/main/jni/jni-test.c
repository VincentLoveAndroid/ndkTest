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
    const char *cString = (*env)->GetStringUTFChars(env, jstring1,
                                                    JNI_FALSE);//这里传null,或JNI_FALSE都可以，但是传JNI_TRUE不可以
    char text[50] = " c改变了java object变量的值哦";
    //拼接字符串
    strcat(text, cString);
    jstring newString = (*env)->NewStringUTF(env, text);
    //改变对象的属性
    (*env)->SetObjectField(env, instance, fieldID, newString);
    return newString;
}
/**
 * 访问date的构造函数，实例化date对象，并且通过getTime()方法返回当前时间戳
 */
JNIEXPORT jlong JNICALL
Java_com_example_administrator_ndktest_jnitest_JNITest_accessConstructor(JNIEnv *env, jclass clz) {
    //得到Date对应的类，类似java中的Class.forName方法
    jclass aClass = (*env)->FindClass(env, "java/util/Date");
    //得到构造函数的methodId,构造函数key固定用"<init>"，签名可以用javap -s -p java.util.Date 查询
    jmethodID constructMethodID = (*env)->GetMethodID(env,aClass , "<init>", "()V");
    //new出date实例，可变长参数列表，可传参数
    jobject dateObject = (*env)->NewObject(env, aClass, constructMethodID);
    //得到getTime方法的methodId
    jmethodID methodID = (*env)->GetMethodID(env, aClass, "getTime", "()J");
    //调用date的getTime方法
    jlong longTime= (*env)->CallLongMethod(env, dateObject, methodID);

    return longTime;

}

JNIEXPORT jobject JNICALL
Java_com_example_administrator_ndktest_jnitest_JNITest_accseeNonvirtualMethod(JNIEnv *env,
                                                                              jclass type) {
    jclass human_clz = (*env)->FindClass(env, "com.example.administrator.ndktest.jnitest.obj.Human");
//    (*env)->GetMethodID(env,"sing",)



    // TODO

}