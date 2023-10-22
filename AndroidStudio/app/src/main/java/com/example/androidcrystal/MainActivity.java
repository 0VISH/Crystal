package com.example.androidcrystal;

import androidx.appcompat.app.AppCompatActivity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.content.Context;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import android.util.Log;
import android.view.Surface;

public class MainActivity extends AppCompatActivity{

    static {
        System.loadLibrary("crystal");
    }
    public native int CrystalMain(Surface surface);

    private GLSurfaceView surfaceView = null;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        surfaceView = new SurfaceView(this);
        setContentView(surfaceView);
    }
    @Override
    public void onStart(){
        super.onStart();
        Surface surface = surfaceView.getHolder().getSurface();
        int result = CrystalMain(surface);
    }

    @Override
    public void onPause(){
        super.onPause();
        surfaceView.onResume();
    }
    @Override
    public void onResume(){
        super.onResume();
        surfaceView.onResume();
    }

}

class SurfaceView extends GLSurfaceView{
    public SurfaceView(Context context){
        super(context);
        setEGLContextClientVersion(3);
        GLSurfaceView.Renderer renderer = new com.example.androidcrystal.Renderer();
        setRenderer(renderer);
    }
}
class Renderer implements GLSurfaceView.Renderer{
    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {

    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int i, int i1) {

    }

    @Override
    public void onDrawFrame(GL10 gl10) {
    }
}