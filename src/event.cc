#include "event.hh"

void EventDispatcher::init(){
    off = 0;
    for(u8 x=0; x<EVENT_COUNT; x+=1){
	events[x].type = EventType::NONE;
    };
};
void EventDispatcher::registerEvent(Event e){
    if(e.type == EventType::NONE){return;};
    if(off >= EVENT_COUNT){return;};
    events[off] = e;
    off += 1;
};
Event EventDispatcher::getEvent(){
    Event e = events[0];
    if(off != 0){
	memcpy(&events[0], &events[1], sizeof(Event)*off);
	off -= 1;
    };
    return e;
};
#if(DBG)
void EventDispatcher::dumpEvents(){
    log("\n[EVENTS]\n");
    for(u8 x=0; x<EVENT_COUNT; x+=1){
	Event e = events[x];
	if(e.type == EventType::NONE){continue;};
	log("[EVENT]\ntype: %d\nbuttonCode: %d\nscroll: %f\n", e.type, e.buttonCode, e.scroll);
    };
};
#endif

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
