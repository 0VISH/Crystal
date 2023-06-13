namespace window{

    typedef HWND Window;
    const char* className = "Crystal";
    bool shouldClose = false;
    EventDispatcher *eventDispatcher;
    
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	LRESULT res = 0;
	Event e;
	e.type = EventType::NONE;
	
        switch(uMsg){
	case WM_QUIT:
	case WM_DESTROY:
	case WM_CLOSE:{
	    shouldClose = true;
	}break;
	case WM_LBUTTONDOWN:{
	    e.type = EventType::MOUSE_BUTTON_DOWN;
	    e.buttonCode = ButtonCode::L_MOUSE;
	};
	case WM_RBUTTONDOWN:{
	    e.type = EventType::MOUSE_BUTTON_DOWN;
	    e.buttonCode = ButtonCode::R_MOUSE;
	};
	case WM_LBUTTONUP:{
	    e.type = EventType::MOUSE_BUTTON_UP;
	    e.buttonCode = ButtonCode::L_MOUSE;
	};
	case WM_RBUTTONUP:{
	    e.type = EventType::MOUSE_BUTTON_UP;
	    e.buttonCode = ButtonCode::R_MOUSE;
	};
	default: res = DefWindowProc(hwnd, uMsg, wParam, lParam);
	};

	eventDispatcher->registerEvent(e);
	return res;
    };
    
    Window create(char *windowName, EventDispatcher *ed){
	eventDispatcher = ed;
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
	    UpdateWindow(hwnd);
	    return hwnd;
	}else{
	    log("could not register class");
	    return NULL;
	};
    };
    void destroy(Window window){
	DestroyWindow(window);
	UnregisterClass(className, NULL);
    };
    
    void pollEvents(){
	MSG msg;
	while(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)){
	    TranslateMessage(&msg);
	    DispatchMessage(&msg);
	    switch(msg.message){
	    case WM_QUIT: shouldClose = true;
	    };
	};
    };
};
