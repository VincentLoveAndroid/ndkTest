package com.example.administrator.ndktest.jnitest;

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
}