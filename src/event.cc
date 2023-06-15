enum class EventType : u8{
    NONE,
    KEY_DOWN,
    KEY_UP,
    MOUSE_BUTTON_DOWN,
    MOUSE_BUTTON_UP,
    MOUSE_SCROLL,
};
enum class ButtonCode : u16{
    //NOTE: this is in peace with imgui's button code
    L_MOUSE = 0,
    R_MOUSE,
    M_MOUSE,
};

struct Event{
    EventType type;
    ButtonCode buttonCode;
    f32 scroll;
};
//NOTE: Block dispatcher. Hence, we hold only 1 event
struct EventDispatcher{
    Event event;

    void registerEvent(Event e){event = e;};
    Event getEvent(){
	Event e = event;
	event.type = EventType::NONE;
	return e;
    };
};

bool isMouseButtonEvent(Event e){
    return e.type == EventType::MOUSE_BUTTON_DOWN || e.type == EventType::MOUSE_BUTTON_UP;
};
bool isKeyboardButtonEvent(Event e){
    return e.type == EventType::KEY_DOWN || e.type == EventType::KEY_UP;
};

#if(DBG)
void dumpEvent(Event e){
    bool dumpOff = false;
    bool isNone = false;
    log("[EVENT]\n");
    log("type: ");
    switch(e.type){
    case EventType::NONE: log("none");isNone=true;break;
    case EventType::KEY_DOWN: log("key_down");break;
    case EventType::KEY_UP: log("key_up");break;
    case EventType::MOUSE_BUTTON_DOWN: log("mouse_button_down");break;
    case EventType::MOUSE_BUTTON_UP: log("mouse_button_up");break;
    case EventType::MOUSE_SCROLL: log("mouse_scroll");dumpOff=true;break;
    default: DEBUG_UNREACHABLE;
    };
    log("\n");
    if(isNone){return;};
    log("button code: ");
    switch(e.buttonCode){
    case ButtonCode::R_MOUSE: log("r_mouse");break;
    case ButtonCode::L_MOUSE: log("l_mouse");break;
    default: log("%c", (char)e.buttonCode);
    };
    log("\n");
    if(dumpOff){
	log("scroll: %f\n", e.scroll);
    };
};
#endif
