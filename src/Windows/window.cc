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
	case WM_DESTROY:
	case WM_QUIT:
	case WM_CLOSE:{
	    shouldClose = true;
	}break;
	case WM_KEYDOWN:{
	    if(wParam == VK_ESCAPE){
		shouldClose = true;
		break;
	    };
	    e.type = EventType::KEY_DOWN;
	    e.buttonCode = (ButtonCode)wParam;
	}break;
	case WM_KEYUP:{
	    e.type = EventType::KEY_UP;
	    e.buttonCode = (ButtonCode)wParam;
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

	WNDCLASSEXW wc = { sizeof(wc), CS_OWNDC, WindowProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, (LPCWSTR)className, NULL };
        ::RegisterClassExW(&wc);
	HWND hwnd = ::CreateWindowW(wc.lpszClassName, (LPCWSTR)windowName, WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);
	return hwnd;
    };
    void destroy(Window window){
	DestroyWindow(window);
	::UnregisterClassW((LPCWSTR)className, GetModuleHandle(NULL));
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
