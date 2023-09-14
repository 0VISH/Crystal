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
    print("\n[EVENTS]\n");
    for(u8 x=0; x<EVENT_COUNT; x+=1){
	Event e = events[x];
	if(e.type == EventType::NONE){continue;};
	print("[EVENT]\ntype: %d\nbuttonCode: %d\nscroll: %f\n", e.type, e.buttonCode, e.scroll);
    };
};
#endif
