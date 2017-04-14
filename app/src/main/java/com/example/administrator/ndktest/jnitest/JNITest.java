package com.example.administrator.ndktest.jnitest;

import java.util.Date;

/**
 * Created by vincent on 2017/4/12.
 * email-address:674928145@qq.com
 * description:
 */

public class JNITest {

    public String name = "hello";

    static {
        System.loadLibrary("jni-test");
    }

    public static native String getStringFromC();

    public native String getStringFromObject();

    public static native long accessConstructor();

    public static native String accessCustomClassMethod();

    public static native String accessNonvirtualMethod();

    public static native String resolveMessyCode();

    public static native int[] getSortResultFromC(int[] arr);

    public static native Date newGlobalRef();

    public static native Date getGlobalRef();

    public static native Date deleteGlobalRef();

    public static native int handleException();


}
