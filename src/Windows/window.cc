ButtonCode Win32VirtualKeyToButtonCode(WPARAM wParam){
    switch (wParam){
    case VK_TAB: return ButtonCode::Key_Tab;
    case VK_LEFT: return ButtonCode::Key_LeftArrow;
    case VK_RIGHT: return ButtonCode::Key_RightArrow;
    case VK_UP: return ButtonCode::Key_UpArrow;
    case VK_DOWN: return ButtonCode::Key_DownArrow;
    case VK_PRIOR: return ButtonCode::Key_PageUp;
    case VK_NEXT: return ButtonCode::Key_PageDown;
    case VK_HOME: return ButtonCode::Key_Home;
    case VK_END: return ButtonCode::Key_End;
    case VK_INSERT: return ButtonCode::Key_Insert;
    case VK_DELETE: return ButtonCode::Key_Delete;
    case VK_BACK: return ButtonCode::Key_Backspace;
    case VK_SPACE: return ButtonCode::Key_Space;
    case VK_RETURN: return ButtonCode::Key_Enter;
    case VK_ESCAPE: return ButtonCode::Key_Escape;
    case VK_OEM_7: return ButtonCode::Key_Apostrophe;
    case VK_OEM_COMMA: return ButtonCode::Key_Comma;
    case VK_OEM_MINUS: return ButtonCode::Key_Minus;
    case VK_OEM_PERIOD: return ButtonCode::Key_Period;
    case VK_OEM_2: return ButtonCode::Key_Slash;
    case VK_OEM_1: return ButtonCode::Key_Semicolon;
    case VK_OEM_PLUS: return ButtonCode::Key_Equal;
    case VK_OEM_4: return ButtonCode::Key_LeftBracket;
    case VK_OEM_5: return ButtonCode::Key_Backslash;
    case VK_OEM_6: return ButtonCode::Key_RightBracket;
    case VK_OEM_3: return ButtonCode::Key_GraveAccent;
    case VK_CAPITAL: return ButtonCode::Key_CapsLock;
    case VK_SCROLL: return ButtonCode::Key_ScrollLock;
    case VK_NUMLOCK: return ButtonCode::Key_NumLock;
    case VK_SNAPSHOT: return ButtonCode::Key_PrintScreen;
    case VK_PAUSE: return ButtonCode::Key_Pause;
    case VK_NUMPAD0: return ButtonCode::Key_Keypad0;
    case VK_NUMPAD1: return ButtonCode::Key_Keypad1;
    case VK_NUMPAD2: return ButtonCode::Key_Keypad2;
    case VK_NUMPAD3: return ButtonCode::Key_Keypad3;
    case VK_NUMPAD4: return ButtonCode::Key_Keypad4;
    case VK_NUMPAD5: return ButtonCode::Key_Keypad5;
    case VK_NUMPAD6: return ButtonCode::Key_Keypad6;
    case VK_NUMPAD7: return ButtonCode::Key_Keypad7;
    case VK_NUMPAD8: return ButtonCode::Key_Keypad8;
    case VK_NUMPAD9: return ButtonCode::Key_Keypad9;
    case VK_DECIMAL: return ButtonCode::Key_KeypadDecimal;
    case VK_DIVIDE: return ButtonCode::Key_KeypadDivide;
    case VK_MULTIPLY: return ButtonCode::Key_KeypadMultiply;
    case VK_SUBTRACT: return ButtonCode::Key_KeypadSubtract;
    case VK_ADD: return ButtonCode::Key_KeypadAdd;
    case VK_LSHIFT: return ButtonCode::Key_LeftShift;
    case VK_LCONTROL: return ButtonCode::Key_LeftCtrl;
    case VK_LMENU: return ButtonCode::Key_LeftAlt;
    case VK_LWIN: return ButtonCode::Key_LeftSuper;
    case VK_RSHIFT: return ButtonCode::Key_RightShift;
    case VK_RCONTROL: return ButtonCode::Key_RightCtrl;
    case VK_RMENU: return ButtonCode::Key_RightAlt;
    case VK_RWIN: return ButtonCode::Key_RightSuper;
    case VK_APPS: return ButtonCode::Key_Menu;
    case '0': return ButtonCode::Key_0;
    case '1': return ButtonCode::Key_1;
    case '2': return ButtonCode::Key_2;
    case '3': return ButtonCode::Key_3;
    case '4': return ButtonCode::Key_4;
    case '5': return ButtonCode::Key_5;
    case '6': return ButtonCode::Key_6;
    case '7': return ButtonCode::Key_7;
    case '8': return ButtonCode::Key_8;
    case '9': return ButtonCode::Key_9;
    case 'A': return ButtonCode::Key_A;
    case 'B': return ButtonCode::Key_B;
    case 'C': return ButtonCode::Key_C;
    case 'D': return ButtonCode::Key_D;
    case 'E': return ButtonCode::Key_E;
    case 'F': return ButtonCode::Key_F;
    case 'G': return ButtonCode::Key_G;
    case 'H': return ButtonCode::Key_H;
    case 'I': return ButtonCode::Key_I;
    case 'J': return ButtonCode::Key_J;
    case 'K': return ButtonCode::Key_K;
    case 'L': return ButtonCode::Key_L;
    case 'M': return ButtonCode::Key_M;
    case 'N': return ButtonCode::Key_N;
    case 'O': return ButtonCode::Key_O;
    case 'P': return ButtonCode::Key_P;
    case 'Q': return ButtonCode::Key_Q;
    case 'R': return ButtonCode::Key_R;
    case 'S': return ButtonCode::Key_S;
    case 'T': return ButtonCode::Key_T;
    case 'U': return ButtonCode::Key_U;
    case 'V': return ButtonCode::Key_V;
    case 'W': return ButtonCode::Key_W;
    case 'X': return ButtonCode::Key_X;
    case 'Y': return ButtonCode::Key_Y;
    case 'Z': return ButtonCode::Key_Z;
    case VK_F1: return ButtonCode::Key_F1;
    case VK_F2: return ButtonCode::Key_F2;
    case VK_F3: return ButtonCode::Key_F3;
    case VK_F4: return ButtonCode::Key_F4;
    case VK_F5: return ButtonCode::Key_F5;
    case VK_F6: return ButtonCode::Key_F6;
    case VK_F7: return ButtonCode::Key_F7;
    case VK_F8: return ButtonCode::Key_F8;
    case VK_F9: return ButtonCode::Key_F9;
    case VK_F10: return ButtonCode::Key_F10;
    case VK_F11: return ButtonCode::Key_F11;
    case VK_F12: return ButtonCode::Key_F12;
    default: return ButtonCode::Key_None;
    };
};
u32 ButtonCodeToWin32VirtualKey(ButtonCode code) {
    switch (code) {
    case ButtonCode::Key_Tab: return VK_TAB;
    case ButtonCode::Key_LeftArrow: return VK_LEFT;
    case ButtonCode::Key_RightArrow: return VK_RIGHT;
    case ButtonCode::Key_UpArrow: return VK_UP;
    case ButtonCode::Key_DownArrow: return VK_DOWN;
    case ButtonCode::Key_PageUp: return VK_PRIOR;
    case ButtonCode::Key_PageDown: return VK_NEXT;
    case ButtonCode::Key_Home: return VK_HOME;
    case ButtonCode::Key_End: return VK_END;
    case ButtonCode::Key_Insert: return VK_INSERT;
    case ButtonCode::Key_Delete: return VK_DELETE;
    case ButtonCode::Key_Backspace: return VK_BACK;
    case ButtonCode::Key_Space: return VK_SPACE;
    case ButtonCode::Key_Enter: return VK_RETURN;
    case ButtonCode::Key_Escape: return VK_ESCAPE;
    case ButtonCode::Key_Apostrophe: return VK_OEM_7;
    case ButtonCode::Key_Comma: return VK_OEM_COMMA;
    case ButtonCode::Key_Minus: return VK_OEM_MINUS;
    case ButtonCode::Key_Period: return VK_OEM_PERIOD;
    case ButtonCode::Key_Slash: return VK_OEM_2;
    case ButtonCode::Key_Semicolon: return VK_OEM_1;
    case ButtonCode::Key_Equal: return VK_OEM_PLUS;
    case ButtonCode::Key_LeftBracket: return VK_OEM_4;
    case ButtonCode::Key_Backslash: return VK_OEM_5;
    case ButtonCode::Key_RightBracket: return VK_OEM_6;
    case ButtonCode::Key_GraveAccent: return VK_OEM_3;
    case ButtonCode::Key_CapsLock: return VK_CAPITAL;
    case ButtonCode::Key_ScrollLock: return VK_SCROLL;
    case ButtonCode::Key_NumLock: return VK_NUMLOCK;
    case ButtonCode::Key_PrintScreen: return VK_SNAPSHOT;
    case ButtonCode::Key_Pause: return VK_PAUSE;
    case ButtonCode::Key_Keypad0: return VK_NUMPAD0;
    case ButtonCode::Key_Keypad1: return VK_NUMPAD1;
    case ButtonCode::Key_Keypad2: return VK_NUMPAD2;
    case ButtonCode::Key_Keypad3: return VK_NUMPAD3;
    case ButtonCode::Key_Keypad4: return VK_NUMPAD4;
    case ButtonCode::Key_Keypad5: return VK_NUMPAD5;
    case ButtonCode::Key_Keypad6: return VK_NUMPAD6;
    case ButtonCode::Key_Keypad7: return VK_NUMPAD7;
    case ButtonCode::Key_Keypad8: return VK_NUMPAD8;
    case ButtonCode::Key_Keypad9: return VK_NUMPAD9;
    case ButtonCode::Key_KeypadDecimal: return VK_DECIMAL;
    case ButtonCode::Key_KeypadDivide: return VK_DIVIDE;
    case ButtonCode::Key_KeypadMultiply: return VK_MULTIPLY;
    case ButtonCode::Key_KeypadSubtract: return VK_SUBTRACT;
    case ButtonCode::Key_KeypadAdd: return VK_ADD;
    case ButtonCode::Key_LeftShift: return VK_LSHIFT;
    case ButtonCode::Key_LeftCtrl: return VK_LCONTROL;
    case ButtonCode::Key_LeftAlt: return VK_LMENU;
    case ButtonCode::Key_LeftSuper: return VK_LWIN;
    case ButtonCode::Key_RightShift: return VK_RSHIFT;
    case ButtonCode::Key_RightCtrl: return VK_RCONTROL;
    case ButtonCode::Key_RightAlt: return VK_RMENU;
    case ButtonCode::Key_RightSuper: return VK_RWIN;
    case ButtonCode::Key_Menu: return VK_APPS;
    case ButtonCode::Key_0: return '0';
    case ButtonCode::Key_1: return '1';
    case ButtonCode::Key_2: return '2';
    case ButtonCode::Key_3: return '3';
    case ButtonCode::Key_4: return '4';
    case ButtonCode::Key_5: return '5';
    case ButtonCode::Key_6: return '6';
    case ButtonCode::Key_7: return '7';
    case ButtonCode::Key_8: return '8';
    case ButtonCode::Key_9: return '9';
    case ButtonCode::Key_A: return 'A';
    case ButtonCode::Key_B: return 'B';
    case ButtonCode::Key_C: return 'C';
    case ButtonCode::Key_D: return 'D';
    case ButtonCode::Key_E: return 'E';
    case ButtonCode::Key_F: return 'F';
    case ButtonCode::Key_G: return 'G';
    case ButtonCode::Key_H: return 'H';
    case ButtonCode::Key_I: return 'I';
    case ButtonCode::Key_J: return 'J';
    case ButtonCode::Key_K: return 'K';
    case ButtonCode::Key_L: return 'L';
    case ButtonCode::Key_M: return 'M';
    case ButtonCode::Key_N: return 'N';
    case ButtonCode::Key_O: return 'O';
    case ButtonCode::Key_P: return 'P';
    case ButtonCode::Key_Q: return 'Q';
    case ButtonCode::Key_R: return 'R';
    case ButtonCode::Key_S: return 'S';
    case ButtonCode::Key_T: return 'T';
    case ButtonCode::Key_U: return 'U';
    case ButtonCode::Key_V: return 'V';
    case ButtonCode::Key_W: return 'W';
    case ButtonCode::Key_X: return 'X';
    case ButtonCode::Key_Y: return 'Y';
    case ButtonCode::Key_Z: return 'Z';
    case ButtonCode::Key_F1: return VK_F1;
    case ButtonCode::Key_F2: return VK_F2;
    case ButtonCode::Key_F3: return VK_F3;
    case ButtonCode::Key_F4: return VK_F4;
    case ButtonCode::Key_F5: return VK_F5;
    case ButtonCode::Key_F6: return VK_F6;
    case ButtonCode::Key_F7: return VK_F7;
    case ButtonCode::Key_F8: return VK_F8;
    case ButtonCode::Key_F9: return VK_F9;
    case ButtonCode::Key_F10: return VK_F10;
    case ButtonCode::Key_F11: return VK_F11;
    case ButtonCode::Key_F12: return VK_F12;
    default: return 0;
    };
};

bool isKeyDown(ButtonCode code){
    return GetAsyncKeyState(ButtonCodeToWin32VirtualKey(code)) & 0x8000;
};

extern  LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace window{
    typedef HWND Window;
    const char* className = "Crystal";

    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	LRESULT res = 0;
	Event e;
	e.type = EventType::NONE;
	
        switch(uMsg){
	case WM_DESTROY:
	case WM_QUIT:
	case WM_CLOSE:{
	    engine->windowX = 0;
	}break;
	case WM_SIZE:{
	    engine->windowX = LOWORD(lParam);
	    engine->windowY = HIWORD(lParam);
	};
	case WM_KEYDOWN:{
	    if(wParam == VK_ESCAPE){
		engine->windowX = 0;
		break;
	    };
	    e.type = EventType::KEY_DOWN;
	    e.buttonCode = Win32VirtualKeyToButtonCode(wParam);
	}break;
	case WM_KEYUP:{
	    e.type = EventType::KEY_UP;
	    e.buttonCode = Win32VirtualKeyToButtonCode(wParam);
	}break;
	case WM_LBUTTONDOWN:{
	    e.type = EventType::MOUSE_BUTTON_DOWN;
	    e.buttonCode = ButtonCode::L_MOUSE;
	}break;
	case WM_RBUTTONDOWN:{
	    e.type = EventType::MOUSE_BUTTON_DOWN;
	    e.buttonCode = ButtonCode::R_MOUSE;
	}break;
	case WM_LBUTTONUP:{
	    e.type = EventType::MOUSE_BUTTON_UP;
	    e.buttonCode = ButtonCode::L_MOUSE;
	}break;
	case WM_RBUTTONUP:{
	    e.type = EventType::MOUSE_BUTTON_UP;
	    e.buttonCode = ButtonCode::R_MOUSE;
	}break;
	case WM_MOUSEWHEEL:{
	    e.type = EventType::MOUSE_SCROLL;
	    e.scroll = (f32)GET_WHEEL_DELTA_WPARAM(wParam);
	}break;
	default: res = DefWindowProc(hwnd, uMsg, wParam, lParam);
	};

	engine->ed.registerEvent(e);
	return res;
    };
    
    Window create(char *windowName, u32 windowX, u32 windowY){
	engine->windowX = windowX;
	engine->windowY = windowY;
	engine->ed.init();

	WNDCLASSEXW wc = { sizeof(wc), CS_OWNDC, WindowProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, (LPCWSTR)className, NULL };
        ::RegisterClassExW(&wc);
	HWND hwnd = ::CreateWindowW(wc.lpszClassName, (LPCWSTR)windowName, WS_OVERLAPPEDWINDOW, 100, 100, windowX, windowY, NULL, NULL, wc.hInstance, NULL);
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
	    case WM_QUIT:
		engine->windowX = 0;
	    };
	};
    };
};
