package com.example.androidcrystal;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity{

    static {
        System.loadLibrary("crystal");
    }
    public native int JNIMain();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        int result = JNIMain();
    }
}
