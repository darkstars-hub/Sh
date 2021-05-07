#include "EventListener.h"

#include "EventMessenger.h"

sh::EventListener::EventListener(sh::ClassID id) :
    class_id_(id),
    events_(){
}

sh::EventListener::~EventListener() {
}

void sh::EventListener::Send(sh::Event& e) {
    sh::EventMessenger::Singleton().Receive(e);
}

void sh::EventListener::Receive(sh::Event& e) {
    events_.push_back(&e);
}

void sh::EventListener::ResetEvents(void) {
    for (auto e : events_) {
        delete e;
        e = nullptr;
    } // for
    events_.clear();
}
