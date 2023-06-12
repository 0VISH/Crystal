#include <stdio.h>

namespace window{

    typedef HWND Window;
    const char* className = "Crystal";
    bool shouldClose = false;
    
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	LRESULT res;
	
        switch(uMsg){
	case WM_DESTROY:
	case WM_CLOSE:{
	    shouldClose = true;
	}break;
	default: res = DefWindowProc(hwnd, uMsg, wParam, lParam);
	};
	
	return res;
    };
    
    Window create(char *windowName){
	HMODULE hInstance = GetModuleHandle(NULL);	
	
	WNDCLASS wc = {};
	wc.lpfnWndProc   = WindowProc;
	wc.hInstance     = hInstance;
	wc.lpszClassName = className;

	if(RegisterClass(&wc)){
	    HWND hwnd = CreateWindowEx(
				       0,                              // Optional window styles.
				       className,                     // Window class
				       windowName,                    // Window text
				       WS_OVERLAPPEDWINDOW,            // Window style

				       // Size and position
				       CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

				       NULL,       // Parent window    
				       NULL,       // Menu
				       hInstance,  // Instance handle
				       NULL        // Additional application data
				       );
	    ShowWindow(hwnd, 1);
	    return hwnd;
	}else{
	    printf("could not register class");
	    return NULL;
	};
    };
    void destroy(Window window){
	DestroyWindow(window);
	UnregisterClass(className, NULL);
    };
    
    void pollEvents(){
	MSG msg;
	BOOL msgResult = GetMessage(&msg, 0, 0, 0);
	if(msgResult > 0){
	    TranslateMessage(&msg);
	    DispatchMessage(&msg);
	};
    };
};
