package com.example.administrator.ndktest;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

import com.example.administrator.ndktest.jnitest.JNITest;

import java.util.Date;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);

//        JNITest jniTest = new JNITest();
//        jniTest.getStringFromObject();
//        String name = jniTest.name;
//        String s = JNITest.accessNonvirtualMethod();
//        tv.setText(s);
//        int arr[] = {1, 2, 3, 4, 5};
//        int[] sortResultFromC = JNITest.getSortResultFromC(arr);
//        for (int i = 0; i < arr.length; i++) {
//            System.out.println(arr[i]);
//        }
//        JNITest.newGlobalRef();
//        Date globalRef = JNITest.getGlobalRef();
//        System.out.println(globalRef.getTime());
//        JNITest.deleteGlobalRef();
//        Date globalRef1 = JNITest.getGlobalRef();
//        System.out.println("哈哈");

        int i = JNITest.handleException();
        System.out.println("解决异常后得到的值是" + i);

        //tv.setText(stringFromJNI());
    }
//
//    /**
//     * A native method that is implemented by the 'native-lib' native library,
//     * which is packaged with this application.
//     */
//    public native String stringFromJNI();
//
//    // Used to load the 'native-lib' library on application startup.
//    static {
//        System.loadLibrary("native-lib");
//    }
}
