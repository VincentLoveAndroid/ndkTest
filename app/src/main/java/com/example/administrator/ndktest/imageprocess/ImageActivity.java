package com.example.administrator.ndktest.imageprocess;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.Toast;

import com.example.administrator.ndktest.R;

public class ImageActivity extends Activity {

    private ImageView imageView;
    private Bitmap bitmap = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_image);

        imageView = (ImageView) findViewById(R.id.iv_test);

        bitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.girl);
    }

    public void source(View view) {
        imageView.setImageResource(R.mipmap.girl);

    }

    public void java(View view) {
        long lastTime = System.currentTimeMillis();
        Bitmap javaBitmap = JavaImageUtil.getBitmap(bitmap);
        imageView.setImageBitmap(javaBitmap);
        Toast.makeText(this, "java处理耗时" + (System.currentTimeMillis() - lastTime) + "ms", Toast.LENGTH_SHORT).show();
    }

    public void ndk(View view) {
        long lastTime = System.currentTimeMillis();
        int width = bitmap.getWidth();
        int height = bitmap.getHeight();
        int[] buffer = new int[width * height];
        bitmap.getPixels(buffer, 0, width, 0, 0, width, height);
        int[] result = NdkImageUtil.getImage(buffer, width, height);
        Bitmap ndkBitmap = Bitmap.createBitmap(result, width, height, Bitmap.Config.ARGB_8888);
        Toast.makeText(this, "ndk处理耗时" + (System.currentTimeMillis() - lastTime) + "ms", Toast.LENGTH_SHORT).show();
        imageView.setImageBitmap(ndkBitmap);
    }
}
