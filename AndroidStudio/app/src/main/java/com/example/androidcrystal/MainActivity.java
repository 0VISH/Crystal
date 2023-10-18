package com.example.androidcrystal;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity{

    static {
        System.loadLibrary("crystal");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
    }
}
