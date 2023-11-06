package com.example.androidcrystal;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;

import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.Window;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MainActivity extends AppCompatActivity{
    static {
        System.loadLibrary("crystal");
    }
    public native void CrystalInit(AssetManager assetManager);
    public native void CrystalUninit();

    private GLSurfaceView glSurfaceView = null;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.activity_main);
        ActionBar actionBar = getSupportActionBar();
        if(actionBar != null){actionBar.hide();};

        glSurfaceView = findViewById(R.id.glSurfaceView);
        Renderer renderer = new Renderer();

        glSurfaceView.setEGLContextClientVersion(3);
        glSurfaceView.setRenderer(renderer);
    }
    @Override
    public void onStart(){
        super.onStart();
        CrystalInit(getAssets());
    }
    @Override
    public void onDestroy(){
        super.onDestroy();
        CrystalUninit();
    }

    @Override
    public void onPause(){
        super.onPause();
        glSurfaceView.onResume();
    }
    @Override
    public void onResume(){
        super.onResume();
        glSurfaceView.onResume();
    }

}
class Renderer implements GLSurfaceView.Renderer{

    static {
        System.loadLibrary("crystal");
    }
    public native void CrystalDraw();
    public native void CrystalUpdate();
    public native void CrystalSurfaceCreated();
    public native void CrystalSurfaceChanged(int x, int y);
    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {

        CrystalSurfaceCreated();
    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int x, int y) {
        CrystalSurfaceChanged(x, y);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        CrystalUpdate();
        CrystalDraw();
    }
}