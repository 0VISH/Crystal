#pragma once

#define EVENT_COUNT 5

enum class EventType : u8{
    NONE,
    KEY_DOWN,
    KEY_UP,
    MOUSE_BUTTON_DOWN,
    MOUSE_BUTTON_UP,
    MOUSE_SCROLL,
};
enum class ButtonCode : u32{
    L_MOUSE = 0,
    R_MOUSE,
    M_MOUSE,
    Key_None,
    Key_Tab,
    Key_LeftArrow,
    Key_RightArrow,
    Key_UpArrow,
    Key_DownArrow,
    Key_PageUp,
    Key_PageDown,
    Key_Home,
    Key_End,
    Key_Insert,
    Key_Delete,
    Key_Backspace,
    Key_Space,
    Key_Enter,
    Key_Escape,
    Key_Apostrophe,
    Key_Comma,
    Key_Minus,
    Key_Period,
    Key_Slash,
    Key_Semicolon,
    Key_Equal,
    Key_LeftBracket,
    Key_Backslash,
    Key_RightBracket,
    Key_GraveAccent,
    Key_CapsLock,
    Key_ScrollLock,
    Key_NumLock,
    Key_PrintScreen,
    Key_Pause,
    Key_Keypad0,
    Key_Keypad1,
    Key_Keypad2,
    Key_Keypad3,
    Key_Keypad4,
    Key_Keypad5,
    Key_Keypad6,
    Key_Keypad7,
    Key_Keypad8,
    Key_Keypad9,
    Key_KeypadDecimal,
    Key_KeypadDivide,
    Key_KeypadMultiply,
    Key_KeypadSubtract,
    Key_KeypadAdd,
    Key_KeypadEnter,
    Key_LeftShift,
    Key_LeftCtrl,
    Key_LeftAlt,
    Key_LeftSuper,
    Key_RightShift,
    Key_RightCtrl,
    Key_RightAlt,
    Key_RightSuper,
    Key_Menu,
    Key_0,
    Key_1,
    Key_2,
    Key_3,
    Key_4,
    Key_5,
    Key_6,
    Key_7,
    Key_8,
    Key_9,
    Key_A,
    Key_B,
    Key_C,
    Key_D,
    Key_E,
    Key_F,
    Key_G,
    Key_H,
    Key_I,
    Key_J,
    Key_K,
    Key_L,
    Key_M,
    Key_N,
    Key_O,
    Key_P,
    Key_Q,
    Key_R,
    Key_S,
    Key_T,
    Key_U,
    Key_V,
    Key_W,
    Key_X,
    Key_Y,
    Key_Z,
    Key_F1,
    Key_F2,
    Key_F3,
    Key_F4,
    Key_F5,
    Key_F6,
    Key_F7,
    Key_F8,
    Key_F9,
    Key_F10,
    Key_F11,
    Key_F12
};

struct Event{
    EventType type;
    union{
	ButtonCode buttonCode;
	f32 scroll;
    };
};
struct EventDispatcher{
    Event event;

    void init();
    void registerEvent(Event e);
    Event getEvent();
#if(DBG)
    void dumpEvents();
#endif
};

bool isMouseButtonEvent(Event e){
    return e.type == EventType::MOUSE_BUTTON_DOWN || e.type == EventType::MOUSE_BUTTON_UP;
};
bool isKeyboardButtonEvent(Event e){
    return e.type == EventType::KEY_DOWN || e.type == EventType::KEY_UP;
};
