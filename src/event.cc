#include "event.hh"

void EventDispatcher::init(){
    event.type = EventType::NONE;
};
void EventDispatcher::registerEvent(Event e){
    if(e.type == EventType::NONE){return;};
    event = e;
};
Event EventDispatcher::getEvent(){
    Event temp = event;
    event.type = EventType::NONE;
    return temp;
};
