package com.example.administrator.ndktest;

/**
 * Created by vincent on 2016/11/4.
 * email-address:674928145@qq.com
 * description:
 */

public class NdkImageUtil {
    static {
        System.loadLibrary("image-lib");
    }

    public static native int[] getImage(int[] buffer, int width, int height);

}
