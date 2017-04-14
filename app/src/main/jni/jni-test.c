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
 * 访问类库date的构造函数，实例化date对象，并且通过getTime()方法返回当前时间戳
 */
JNIEXPORT jlong JNICALL
Java_com_example_administrator_ndktest_jnitest_JNITest_accessConstructor(JNIEnv *env, jclass clz) {
    //得到Date对应的类，类似java中的Class.forName方法
    jclass aClass = (*env)->FindClass(env, "java/util/Date");
    //得到构造函数的methodId,构造函数key固定用"<init>"，签名可以用javap -s -p java.util.Date 查询
    jmethodID constructMethodID = (*env)->GetMethodID(env, aClass, "<init>", "()V");
    //new出date实例，可变长参数列表，可传参数
    jobject dateObject = (*env)->NewObject(env, aClass, constructMethodID);
    //得到getTime方法的methodId
    jmethodID methodID = (*env)->GetMethodID(env, aClass, "getTime", "()J");
    //调用date的getTime方法
    jlong longTime = (*env)->CallLongMethod(env, dateObject, methodID);

    return longTime;

}
/**
 * 访问自定义类的函数
 */
JNIEXPORT jstring JNICALL
Java_com_example_administrator_ndktest_jnitest_JNITest_accessCustomClassMethod(JNIEnv *env,
                                                                               jclass type) {
    jclass human_clz = (*env)->FindClass(env,
                                         "com/example/administrator/ndktest/jnitest/obj/Human");
    jmethodID constructMethodID = (*env)->GetMethodID(env, human_clz, "<init>", "()V");

    jobject newObject = (*env)->NewObject(env, human_clz, constructMethodID);

    jmethodID methodID = (*env)->GetMethodID(env, human_clz, "sing", "()Ljava/lang/String;");

    jstring humanSing = (*env)->CallObjectMethod(env, newObject,
                                                 methodID);//jString属于Object因此，用CallObjectMethod
    return humanSing;
}

/**
 * 通过子类的对象和父类的类名，访问父类的函数
 */
JNIEXPORT jstring JNICALL
Java_com_example_administrator_ndktest_jnitest_JNITest_accessNonvirtualMethod(JNIEnv *env,
                                                                              jclass type) {
    //获取子类
    jclass man_clz = (*env)->FindClass(env,
                                       "com/example/administrator/ndktest/jnitest/obj/Man");
    jmethodID constructMethodID = (*env)->GetMethodID(env, man_clz, "<init>", "()V");

    jobject man_object = (*env)->NewObject(env, man_clz, constructMethodID);

    jmethodID methodID = (*env)->GetMethodID(env, man_clz, "sing", "()Ljava/lang/String;");

    //获取父类
    jclass human_clz = (*env)->FindClass(env,
                                         "com/example/administrator/ndktest/jnitest/obj/Human");

    //通过子类的对象调用父类的构造函数
    jstring humanSing = (*env)->CallNonvirtualObjectMethod(env, man_object, human_clz,
                                                           methodID);//jString属于Object因此，用CallObjectMethod

    return humanSing;
}

JNIEXPORT jstring JNICALL
Java_com_example_administrator_ndktest_jnitest_JNITest_resolveMessyCode(JNIEnv *env, jclass type) {


    jstring returnValue;
    return (*env)->NewStringUTF(env, returnValue);
}

JNIEXPORT jintArray JNICALL
Java_com_example_administrator_ndktest_jnitest_JNITest_getSortResultFromC(JNIEnv *env, jclass type,
                                                                          jintArray arr_) {
    jint *arr = (*env)->GetIntArrayElements(env, arr_, NULL);//得到数组的指针
    jsize length = (*env)->GetArrayLength(env, arr_);//得到数组的长度
//    int size = length / sizeof(int);
    int i = 0;
    for (; i < length; i++) {
        arr[i] += 5;
    }
    /**
     * mode
     * 0                            复制回内容并释放elems 缓冲区
     * JNI_COMMIT               复制回内容但不释放elems 缓冲区
     * JNI_ABORT                   释放缓冲区但不复制回变化
     */
    (*env)->ReleaseIntArrayElements(env, arr_, arr, 0);

    return arr_;
}


static jobject globalRef;
/**
 * 创建全局引用
 */
JNIEXPORT jobject JNICALL
Java_com_example_administrator_ndktest_jnitest_JNITest_newGlobalRef(JNIEnv *env, jclass type) {
    jclass cls = (*env)->FindClass(env, "java/util/Date");
    jmethodID constructorId = (*env)->GetMethodID(env, cls, "<init>", "()V");
    jobject object = (*env)->NewObject(env, cls, constructorId);
    globalRef = (*env)->NewGlobalRef(env, object);
}

JNIEXPORT jobject JNICALL
Java_com_example_administrator_ndktest_jnitest_JNITest_getGlobalRef(JNIEnv *env, jclass type) {
    return globalRef;
}
/**
 * 释放全局引用
 */
JNIEXPORT jobject JNICALL
Java_com_example_administrator_ndktest_jnitest_JNITest_deleteGlobalRef(JNIEnv *env, jclass type) {
    (*env)->DeleteGlobalRef(env, globalRef);
}

/**
 * 异常处理
 */
JNIEXPORT jint JNICALL
Java_com_example_administrator_ndktest_jnitest_JNITest_handleException(JNIEnv *env, jclass type) {
//    int i = 5 % 0;
    jint i = 0;
    jclass cls = (*env)->FindClass(env, "java/util/Date");
    (*env)->GetMethodID(env, cls, "<inits>", "()V");
    jthrowable occurred = (*env)->ExceptionOccurred(env);
    if (occurred != NULL) {
        //清除异常
        (*env)->ExceptionClear(env);
        //补救措施
        i = 5;
    }
    if (i == 5) {
        //找到对应的异常类
        jclass cls = (*env)->FindClass(env, "java/lang/IllegalArgumentException");
        //抛出异常给java层
        (*env)->ThrowNew(env, cls, "this value is invalid!");
    }
    return i;
}